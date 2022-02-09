#include "writeToFile.h"
#include "Header.h"

void saveListToBinFile(char* file_name, chessPosList* pos_list) {
	
	FILE* fp;
	short int counterPlaces = 0;
	int sumBitsLeft = SUMBITSINBYTE, nodeToScan = ROW, rem = 0;
	chessPosCell* curr = pos_list->head;
	BYTE pos, MASK = 0, savePos;

	fp = fopen(file_name, "wb");
	checkOpenFile(fp);

	fwrite(&counterPlaces, sizeof(short int), 1, fp);/*save place to size*/

	while (curr != NULL) {

		/*scan the next position to insert*/
		{
			if (nodeToScan == ROW) {
				pos = (((curr->position)[0]) - 'A');
				nodeToScan = COL;
			}
			else {/*nodeToScan is COL*/
				pos = ((curr->position)[1]) - '1';
				nodeToScan = ROW;
				counterPlaces++;
				curr = curr->next;
			}
		}

		if (sumBitsLeft > 2) {
			pos = pos << (sumBitsLeft - SUMBITSINPOS);
			sumBitsLeft = sumBitsLeft - SUMBITSINPOS;
			MASK = MASK | pos;

			if (sumBitsLeft == 0) {

				fwrite(&MASK, sizeof(BYTE), 1, fp);
				initStartVlues(&sumBitsLeft, &MASK);
			}
		}

		else if (sumBitsLeft <= 2 && sumBitsLeft > 0) {
			rem = SUMBITSINPOS - sumBitsLeft;
			savePos = pos;
			pos = pos >> rem;
			MASK = MASK | pos;

			fwrite(&MASK, sizeof(BYTE), 1, fp);
		
			/*initiate the starting values*/
			initStartVlues(&sumBitsLeft, &MASK);

			/*insert the rem to next byte*/
			pos = savePos << (sumBitsLeft - rem);
			sumBitsLeft = sumBitsLeft - rem;
			MASK = MASK | pos;
		}
	}

	if (sumBitsLeft != SUMBITSINBYTE) {
		fwrite(&MASK, sizeof(BYTE), 1, fp);
	}

	fseek(fp, 0, SEEK_SET);
	fwrite(&counterPlaces, sizeof(short int), 1, fp);

	fclose(fp);
	return;
}
void initStartVlues(int* sumBitsLeft, BYTE* MASK) {

	*sumBitsLeft = SUMBITSINBYTE;
	*MASK = 0;
}