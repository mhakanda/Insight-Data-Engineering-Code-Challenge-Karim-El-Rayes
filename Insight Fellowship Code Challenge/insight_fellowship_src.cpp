/****************************************************************/
/*	Insight Data Engineering - Coding Challenge         		*/
/*	Author: Karim El-Rayes				    					*/
/*	Author's email: kelrayes@uwaterloo.ca		    			*/
/*	Document: insight_fellowship_src.cpp 				    	*/
/*	Description: C++ source code	    						*/
/****************************************************************/
//Header files
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>			//comment this line before compiling in Linux, Unix or Mac OS
#include <sys/stat.h>

//Definitions
#define BufferSize 1024		//Read buffer size - here defined by 1024 bytes
#define TweetSize 512		//Twitter tweet size is 140 characters
#define NumOfTweet 32

//Compare function for string sorting - Author: http://www.anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml
int cstring_cmp(const void *a, const void *b) 
{ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
} 

//Compare function for numbers sorting
int cnum_cmp(const void *f,const void *g)
{
	const char *a = (const char *)f;  //pointer type casting
    const char *b = (const char *)g;
    if(*a == *b)
		return 0;
	else if(*a < *b)
		return -1;
	else
		return 1;
}

int main(int argc, char** argv) 
{
	//Variables
	FILE * tweet_in;
	FILE * tweet_out;
	FILE * tmp_file;
	FILE * median;
	char buffer[BufferSize] = "\0";					//General data buffer
	char ft2buffer[BufferSize] = "\0";
	char * pch = NULL;
	char * wpt = NULL;
	char * tok;
	char *words[512] = {" "};						//Words & sorted words buffer, Note: strcmp doesn't work with NULL arrays, don't fill it with NULL
	char TweetBuffer[TweetSize] = "\0";				//Tweets buffer
	char *Tweets[NumOfTweet] = {" "};				//Buffer to hold words per tweet
	char *TmpTweet[20] = {" "};						//Temporary buffer
	char tmp = NULL;
	int FileSize;
	int count = 0;
	int TotalWordCount = 0;
	int i = 0, j = 0;
	int counter = 1;
	int InitLocation = 0;
	int TweetNumber = 0;
	int WordsPerTweet[NumOfTweet] = {0};
	int * DynamicBuffer = NULL;
	int DynamicBufferSize = 0;
	double OddMedian = 0;
	double EvenMedian = 0;
	double WordsMedian = 0.0;
	size_t LocateChr = 0;
	size_t strings_len = sizeof(words) / sizeof(char *);
	size_t SizeofTweet = sizeof(TmpTweet) / sizeof(char *);

	//Create "tweet_out" directory
	#if defined(_WIN32)
		_mkdir("tweet_output");
	#elif defined(__linux__) 
		mkdir("tweet_output", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); 
	#endif

	//Files I/O initialization
	tweet_in = fopen("tweet_input/tweets.txt", "rb");			//Input file
	tweet_out = fopen("tweet_output/ft1.txt","w+");				//feature 1 output file
	tmp_file = fopen("Tempfile.txt","w+");						//temporary file
	median = fopen("tweet_output/ft2.txt","w+");				//feature 2 output file	

	//Read data from input file
	if(tweet_in != NULL)
	{
		//Read tweets and save it to program buffer
		FileSize = fread(buffer, sizeof(char), sizeof(buffer), tweet_in);			//Read tweets from input file
		fclose(tweet_in);
		//printf("%s", buffer);														//Print file content
		printf("\nFile is: %d bytes\n", FileSize);									//Print file size in bytes
		memcpy(ft2buffer, buffer, FileSize);										//Make a copy of the buffer for feature 2.

		//Feature 1 implementation
		//Counting number of words algorithm: 
		for(count = 0; count <= FileSize; count++)
		{
			if(buffer[count] != ' ')
			{	
				fprintf(tmp_file, "%c", buffer[count]);
			}
			else if(buffer[count] == ' ')					//spaces between words indicates beginning and end of a word
			{
				fprintf(tmp_file, "\n");
				TotalWordCount++;
			}
			if(buffer[count] == '\n')						//New line indicates beginning of a new word/tweet
			{
				TotalWordCount++;
			}
			if(buffer[count] == '\0')						//Detect end of file from the NULL character
			{
				TotalWordCount++;
			}
		}
		printf("Word count is: %d\n", TotalWordCount);		//Print total number of words in the "tweets.txt" file
		fclose(tmp_file);
	}

	//Splitting tweets into tokens then store each token in a string:
	pch = strtok(buffer, "\n ");
	while(pch != NULL)
	{
		words[i] = pch;
		pch = strtok(NULL, "\n ");
		//printf("word %d is: %s\n", i, words[i]);
		i++;
	}
	
	//Sorting words ascendingly
    qsort(words, TotalWordCount, sizeof(char *), cstring_cmp);
	
	//Indicate repetition of words - Implementation of the first feature 
	counter = 1;
	j = 0;
	for(i = 0; i < TotalWordCount-1; i++)
	{
		if(!strcmp(words[j],words[j+1]))
		{	
			counter++;
			//printf("string \"%s\" counted %d\n", words[j], counter);
			//Procedure to avoid skipping the last element in the strings array
			if((j+1) == (TotalWordCount-1))
			{
				//printf("This is the last string \"%s\" detected\n", words[j+1], counter);
				fprintf(tweet_out, "%s\t%d", words[j+1], counter);
			}
		}
		else //if(strcmp(words[j],words[j+1]) != 0)
		{
			fprintf(tweet_out, "%s\t%d\n", words[j], counter);
			counter = 1;
			//printf("new string \"%s\" detected\n", words[j+1], counter);
			//Procedure to avoid skipping the last element in the strings array
			if((j+1) == (TotalWordCount-1))
			{
				//printf("This is the last string \"%s\" detected\n", words[j+1], counter);
				fprintf(tweet_out, "%s\t%d", words[j+1], counter);
			}
		}
		j++;
	}	
	fclose(tweet_out);

	//Feature 2 implementation
	//Splitting tweets
	InitLocation = 0;
	j = 0;
	wpt = strchr(ft2buffer,'\n');
	while (wpt != NULL)
	{
		//printf ("New line found at position %d\n",wpt-ft2buffer+1);
		LocateChr = wpt-ft2buffer-1;
		memcpy(TweetBuffer, ft2buffer+InitLocation, LocateChr-InitLocation);
		InitLocation = LocateChr+1;
		wpt = strchr(wpt+1,'\n');	
		Tweets[TweetNumber] = TweetBuffer;
		//printf("tweet number %d is: %s\n", TweetNumber, Tweets[TweetNumber]);
		
		//Split the tweet to tokens
		tok = strtok (Tweets[TweetNumber]," ");
		while (tok != NULL)
		{
			TmpTweet[j] = tok;
			//printf ("%s %d\n",tok, j);
			tok = strtok (NULL, " ");
			j++;
		}
		//Sort the tweet, avoid duplicated words then count them. 
		qsort(TmpTweet, j, sizeof(char *), cstring_cmp);

		//Calculate number of unique words per tweet
		for(count=0; count < j; count++)
		{
			if(TmpTweet[count+1] != NULL)
			{
				if(strcmp(TmpTweet[count], TmpTweet[count+1]) != 0)
				{
					WordsPerTweet[TweetNumber]++;
				}
			}
			//printf("Sorted tweet is: %s\n", TmpTweet[count]); 
		}
		WordsPerTweet[TweetNumber] = WordsPerTweet[TweetNumber]+1;
		printf("Number of unique words per tweet is %d\n", WordsPerTweet[TweetNumber]);
		
		//Calculating the median of unique words with every incoming tweeet
		//Step 1: Create a dymaic buffer
		DynamicBuffer = (int*) calloc(TweetNumber+1, sizeof(int));
		//Step 2: fill the buffer with something
		for(count=0; count < TweetNumber+1; count++)
		{
			DynamicBuffer[count] = WordsPerTweet[count];
			//printf("Content of dynamic buffer is %d\n", DynamicBuffer[count]);
		}
		//step 3: Sort elements in DynamicBuffer 
		qsort(DynamicBuffer, sizeof(DynamicBuffer)/sizeof(int), sizeof(int), cnum_cmp);
		for(count=0; count < TweetNumber+1; count++)
		{
			//printf("Sorted Dynamic buffer is %d\n", DynamicBuffer[count]);
			if(count == TweetNumber)
			{
				DynamicBufferSize = count+1;
			}
		}
		//Step 4: Calculate median
		if(DynamicBufferSize == 1)
		{
			fprintf(median, "Median is %d\n", DynamicBuffer[DynamicBufferSize-1]);
			//printf("Median is %d\n", DynamicBuffer[DynamicBufferSize-1]);
		}
		else if(DynamicBufferSize%2)	//For odd number of elements
		{	
			OddMedian = (double(DynamicBufferSize)/2) -0.5;
			fprintf(median, "Median is %f\n", DynamicBuffer[int(OddMedian)]);
			//printf("Median element is %f which is %d\n", OddMedian, DynamicBuffer[int(OddMedian)]);
		}
		else				//For even number of elements
		{
			EvenMedian = double(DynamicBuffer[DynamicBufferSize/2] + DynamicBuffer[(DynamicBufferSize/2) - 1])/2;
			fprintf(median, "Median is %f\n", EvenMedian);
			//printf("Median elements are %d and %d with values %d and %d and their average is %f\n", DynamicBufferSize/2, (DynamicBufferSize/2) - 1, 
			//	DynamicBuffer[DynamicBufferSize/2], DynamicBuffer[(DynamicBufferSize/2) - 1], EvenMedian);

		}
		//Step 5: free the buffer
		free(DynamicBuffer);
		TweetNumber++;
		j = 0;
	}
	//Procedure to avoid skipping last tweet
	for(i=0; i<=FileSize; i++)
	{
		if(ft2buffer[i] == NULL)
		{
			memcpy(TweetBuffer, ft2buffer+InitLocation+1, i-LocateChr);
			//printf("last tweet is %s\n", TweetBuffer);
			Tweets[TweetNumber] = TweetBuffer;
			//printf("last tweet number %d is: %s\n", TweetNumber, Tweets[TweetNumber]);
			
			//Split the tweet to tokens
			tok = strtok (Tweets[TweetNumber]," ");
			while (tok != NULL)
			{
				TmpTweet[j] = tok;
				//printf ("%s %d\n",tok, j);
				tok = strtok (NULL, " ");
				j++;
			}

			//Sort the tweet, avoid duplicated words then count them. 
			qsort(TmpTweet, j, sizeof(char *), cstring_cmp);	
			
			//Calculate number of unique words per tweet
			for(count=0; count < j-1; count++)	//Display sorted words
			{
				if(TmpTweet[count+1] != NULL)
				{
					if(strcmp(TmpTweet[count], TmpTweet[count+1]) != 0)
					{
						WordsPerTweet[TweetNumber]++;
					}
				}
				//printf("Sorted tweet is: %s\n", TmpTweet[count]); 
			}
			WordsPerTweet[TweetNumber] = WordsPerTweet[TweetNumber]+1;
			printf("Number of unique words per tweet is %d\n", WordsPerTweet[TweetNumber]);
	
			//Calculating the median of unique words for the last tweeet
			//Step 1: Create a dymaic buffer
			DynamicBuffer = (int*) calloc(TweetNumber+1, sizeof(int));
			//Step 2: fill the buffer with something
			for(count=0; count < TweetNumber+1; count++)
			{
				DynamicBuffer[count] = WordsPerTweet[count];
				//printf("Content of dynamic buffer is %d\n", DynamicBuffer[count]);
			}
			//step 3: Sort elements in DynamicBuffer 
			qsort(DynamicBuffer, sizeof(DynamicBuffer)/sizeof(int), sizeof(int), cnum_cmp);
			for(count=0; count < TweetNumber+1; count++)
			{
				printf("Sorted Dynamic buffer is %d\n", DynamicBuffer[count]);
				if(count == TweetNumber)
				{
					DynamicBufferSize = count+1;
				}
			}
			//Step 4: Calculate median
			if(DynamicBufferSize == 1)
			{
				fprintf(median, "Median is %d\n", DynamicBuffer[DynamicBufferSize-1]);
				//printf("Median is %d\n", DynamicBuffer[DynamicBufferSize-1]);
			}
			else if(DynamicBufferSize%2)	//For odd number of elements
			{	
				OddMedian = (double(DynamicBufferSize)/2) -0.5;
				fprintf(median, "Median is %d\n", DynamicBuffer[int(OddMedian)]);
				printf("Median element is %f which is %d\n", OddMedian, DynamicBuffer[int(OddMedian)]);
			}
			else				//For even number of elements
			{
				EvenMedian = double(DynamicBuffer[DynamicBufferSize/2] + DynamicBuffer[(DynamicBufferSize/2) - 1])/2;
				fprintf(median, "Median is %f\n", EvenMedian);
				//printf("Median elements are %d and %d with values %d and %d and their average is %f\n", DynamicBufferSize/2, (DynamicBufferSize/2) - 1, 
				//	DynamicBuffer[DynamicBufferSize/2], DynamicBuffer[(DynamicBufferSize/2) - 1], EvenMedian);

			}
			//Step 5: free the buffer
			free(DynamicBuffer);
			j = 0;
		}
	}
	fclose(median);		
	scanf("%c", &tmp);
	return 0;
}