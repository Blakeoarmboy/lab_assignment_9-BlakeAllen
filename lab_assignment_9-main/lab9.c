#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
	struct RecordType* next;
};

void setRecordType(struct RecordType* RecordType, int key, char value, int order)
{
    RecordType->id = key;
    RecordType->name = value;
	RecordType->order = order;
    RecordType->next = NULL;
    return;
};
// Fill out this structure
struct HashType
{
	int numOfElements, capacity;
    struct RecordType** arr;
};

// Compute the hash function
int hash(int x, struct HashType* mp)
{
	int bucketIndex;
    int sum = 0, factor = 31;
    for (int i = 0; i < (x%10); i++) {
 
        sum = ((sum % mp->capacity) + (x * factor) % mp->capacity) % mp->capacity;
 
        factor = ((factor % INT_MAX)* (31 % INT_MAX))% INT_MAX;
    }
 
    bucketIndex = sum;
    return bucketIndex;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

void insert(struct HashType* mp, int id, char name, int order)
{
 
    int bucketIndex = hash(id, mp);
    struct RecordType* newNode = (struct RecordType*)malloc(
 
        // Creating a new node
        sizeof(struct RecordType));
 
    // Setting value of node
    setRecordType(newNode, id, name, order);
 
    // Bucket index is empty....no collision
    if (mp->arr[bucketIndex] == NULL) {
        mp->arr[bucketIndex] = newNode;
    }
 
    // Collision
    else {
 
        newNode->next = mp->arr[bucketIndex];
        mp->arr[bucketIndex] = newNode;
    }
    return;
}
 
void delete (struct HashType* mp, int key)
{
 
    int bucketIndex = hash(key, mp);
 
    struct RecordType* prevNode = NULL;
    struct RecordType* currNode = mp->arr[bucketIndex];
 
    while (currNode != NULL) {
 
        if (key== currNode->id) {
 
            if (currNode == mp->arr[bucketIndex]) {
                mp->arr[bucketIndex] = currNode->next;
            }
 
            else {
                prevNode->next = currNode->next;
            }
            free(currNode);
            break;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
    return;
}

char search(struct HashType* mp, int key)
{

    int bucketIndex = hash(key, mp);

    struct RecordType* bucketHead = mp->arr[bucketIndex];
    while (bucketHead != NULL) {

        if (bucketHead->id == key) {
            return bucketHead->name;
        }
        bucketHead = bucketHead->next;
    }
 
    char* errorMssg = (char*)malloc(sizeof(char) * 25);
    printf("Oops! No data found returning NULL Terminator.\n");
    return '\0';
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		if(&pHashArray->arr[i] != NULL){
			printf("%d  %c  %d\n",pHashArray->arr[i]->id, pHashArray->arr[i]->name, pHashArray->arr[i]->order);
		}
		
	}
}

int main(void)
{
	struct RecordType *pRecords;
	struct RecordType *FinalRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	struct HashType *pArr;
	pArr->capacity = 100;
    pArr->numOfElements = 0;
 
    // array of size = 1
    pArr->arr = (struct RecordType**)malloc(sizeof(struct RecordType*) * pArr->capacity);
	for(int i = 0; i < recordSz; i++){
		insert(pArr, pRecords[i].id, pRecords[i].name,pRecords[i].order);
	}


}