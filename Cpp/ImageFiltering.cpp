#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hInfo,
	RGBQUAD* hRGB, BYTE* Output, int W, int H, const char* FileName)
{
	FILE* fp = fopen(FileName, "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(Output, sizeof(BYTE), W * H, fp);
	fclose(fp);
}

void swap(BYTE* a, BYTE* b)
{
	BYTE temp = *a;
	*a = *b;
	*b = temp;
}

BYTE Median(BYTE* arr, int size)
{
	// �������� ����, ��������
	const int S = size;
	for (int i = 0; i < size - 1; i++) // pivot index
	{
		for (int j = i + 1; j < size; j++) // �񱳴�� index
		{
			if (arr[i] > arr[j]) 	swap(&arr[i], &arr[j]);
		}
	}
	return arr[S / 2];
}

BYTE MaxPooling(BYTE* arr, int size)
{
	// �������� ����
	const int S = size;
	for (int i = 0; i < size - 1; i++) // pivot index
	{
		for (int j = i + 1; j < size; j++) // �񱳴�� index
		{
			if (arr[i] > arr[j]) 	swap(&arr[i], &arr[j]);
		}
	}
	return arr[S - 1];// ���� ū ��
}

BYTE MinPooling(BYTE* arr, int size)
{
	// �������� ����
	const int S = size;
	for (int i = 0; i < size - 1; i++) // pivot index
	{
		for (int j = i + 1; j < size; j++) // �񱳴�� index
		{
			if (arr[i] > arr[j]) 	swap(&arr[i], &arr[j]);
		}
	}
	return arr[0];
}

int main()
{
	BITMAPFILEHEADER hf; // 14����Ʈ
	BITMAPINFOHEADER hInfo; // 40����Ʈ
	RGBQUAD hRGB[256]; // 1024����Ʈ
	FILE* fp;
	fp = fopen("data/lenna_impulse.bmp", "rb");
	if (fp == NULL) {
		printf("File not found!\n");
		return -1;
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);
	int ImgSize = hInfo.biWidth * hInfo.biHeight;
	BYTE* Image = (BYTE*)malloc(ImgSize);
	BYTE* Temp = (BYTE*)malloc(ImgSize); // �ӽù迭
	BYTE* Output = (BYTE*)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);
	fclose(fp);

	int Histo[256] = { 0 };
	int AHisto[256] = { 0 };

	/*ObtainHistogram(Image, Histo, hInfo.biWidth, hInfo.biHeight);
	ObtainAHistogram(Histo, AHisto);
	HistogramEqualization(Image, Output, AHisto, hInfo.biWidth, hInfo.biHeight);*/
	/*int Thres = GozalezBinThresh();
	Binarization(Image, Output, hInfo.biWidth, hInfo.biHeight, Thres);*/

	//GaussAvrConv(Image, Output, hInfo.biWidth, hInfo.biHeight);

	/*Sobel_X_Conv(Image, Temp, hInfo.biWidth, hInfo.biHeight);
	Sobel_Y_Conv(Image, Output, hInfo.biWidth, hInfo.biHeight);
	for (int i = 0; i < ImgSize; i++) {
		if (Temp[i] > Output[i]) 	Output[i] = Temp[i];
	}
	Binarization(Output, Output, hInfo.biWidth, hInfo.biHeight, 40);*/
	/*GaussAvrConv(Image, Temp, hInfo.biWidth, hInfo.biHeight);
	Laplace_Conv_DC(Temp, Output, hInfo.biWidth, hInfo.biHeight);*/

	//HistogramStretching(Image, Output, Histo, hInfo.biWidth, hInfo.biHeight);
	//InverseImage(Image, Output, hInfo.biWidth, hInfo.biHeight);
	//BrightnessAdj(Image, Output, hInfo.biWidth, hInfo.biHeight, 70);
	//ContrastAdj(Image, Output, hInfo.biWidth, hInfo.biHeight, 0.5);

	/* Median filtering */
	//byte temp[9];
	//int w = hInfo.biWidth, h = hInfo.biHeight;
	//int i, j;
	//for (i = 1; i < h - 1; i++) {//y��ǥ
	//	for (j = 1; j < w - 1; j++) {//x��ǥ
	//		temp[0] = Image[(i - 1) * w + j-1];
	//		temp[1] = Image[(i - 1) * w + j];
	//		temp[2] = Image[(i - 1) * w + j+1];
	//		temp[3] = Image[i * w + j-1];
	//		temp[4] = Image[i * w + j];
	//		temp[5] = Image[i * w + j+1];
	//		temp[6] = Image[(i + 1) * w + j-1];
	//		temp[7] = Image[(i + 1) * w + j];
	//		temp[8] = Image[(i + 1) * w + j+1];
	//		Output[i * w + j] = Median(temp, 9);// median ���� ��ȯ
	//		//output[i * w + j] = maxpooling(temp, 9);// pepper noise�� ��ȯ
	//		//output[i * w + j] = minpooling(temp, 9);// salt noise�� ��ȯ
	//	}
	//	
	//}

	int length = 15;  // ����ũ�� �� ���� ����

	int margin = length / 2;// ���� �� ó��

	int wsize = length * length;// window ũ��

	byte* temp = (byte*)malloc(sizeof(byte) * wsize);// ����ũ�� ���̰� ���ϱ� ������ ���� �Ҵ�

	int w = hInfo.biWidth, h = hInfo.biHeight; // h,w��

	int i, j, m, n;

	for (i = margin; i < h - margin; i++) { // y��ǥ

		for (j = margin; j < w - margin; j++) {// x��ǥ

			for (m = -margin; m <= margin; m++) { // Kernel��

				for (n = -margin; n <= margin; n++) {// Kernel ��

					temp[(m + margin) * length + (n + margin)] = Image[(i + m) * w + j + n]; // �� temp�� ����

				}

			}

		Output[i * w + j] = Median(temp, wsize);// median�� output�� �ֱ�

		}

	}

	free(temp);
	/* Median filtering */


	SaveBMPFile(hf, hInfo, hRGB, Output, hInfo.biWidth, hInfo.biHeight, "data/median_0.bmp");


	free(Image);
	free(Output);
	free(Temp);
	return 0;
}