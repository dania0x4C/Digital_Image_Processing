#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>


void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hInfo,
	RGBQUAD* hRGB, BYTE* Output, int W, int H, const char* FileName)
{
	FILE* fp = fopen(FileName, "wb");
	if (hInfo.biBitCount == 24) {
		fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
		fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
		fwrite(Output, sizeof(BYTE), W * H * 3, fp);
	}
	else if (hInfo.biBitCount == 8) {
		fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
		fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
		fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
		fwrite(Output, sizeof(BYTE), W * H, fp);
	}
	fclose(fp);
}

void swap(BYTE* a, BYTE* b)
{
	BYTE temp = *a;
	*a = *b;
	*b = temp;
}

void VerticalFlip(BYTE* Img, int W, int H)
{
	for (int i = 0; i < H / 2; i++) { // y��ǥ
		for (int j = 0; j < W; j++) { // x��ǥ
			swap(&Img[i * W + j], &Img[(H - 1 - i) * W + j]);
		}
	}
}

void HorizontalFlip(BYTE* Img, int W, int H)
{
	for (int i = 0; i < W / 2; i++) { // x��ǥ
		for (int j = 0; j < H; j++) { // y��ǥ
			swap(&Img[j * W + i], &Img[j * W + (W - 1 - i)]);
		}
	}
}

void Translation(BYTE* Image, BYTE* Output, int W, int H, int Tx, int Ty)
{
	// Translation
	Ty *= -1;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if ((i + Ty < H && i + Ty >= 0) && (j + Tx < W && j + Tx >= 0))
				Output[(i + Ty) * W + (j + Tx)] = Image[i * W + j];
		}
	}
}

void Scaling(BYTE* Image, BYTE* Output, int W, int H, double SF_X, double SF_Y)
{
	// Scaling
	int tmpX, tmpY;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			tmpX = (int)(j / SF_X);
			tmpY = (int)(i / SF_Y);
			if (tmpY < H && tmpX < W)
				Output[i * W + j] = Image[tmpY * W + tmpX];
		}
	}

}

void Rotation(BYTE* Image, BYTE* Output, int W, int H, int Angle)
{
	int tmpX, tmpY;
	double Radian = Angle * 3.141592 / 180.0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			tmpX = (int)(cos(Radian) * j + sin(Radian) * i);
			tmpY = (int)(-sin(Radian) * j + cos(Radian) * i);
			if ((tmpY < H && tmpY >= 0) && (tmpX < W && tmpX >= 0))
				Output[i * W + j] = Image[tmpY * W + tmpX];
		}
	}
}



// Img: �簢���� �׸� �̹����迭, W: ���� ���λ�����, H: ���� ���λ�����,
// LU_X: �簢���� ������� X��ǥ, LU_Y: �簢���� ������� Y��ǥ,
// RD_X: �簢���� �����ϴ� X��ǥ, LU_Y: �簢���� �����ϴ� Y��ǥ.
void DrawRectOutline(BYTE* Img, int W, int H, int LU_X, int LU_Y, int RD_X, int RD_Y)
{
	for (int i = LU_X; i < RD_X; i++) 	Img[LU_Y * W + i] = 255;
	for (int i = LU_X; i < RD_X; i++) 	Img[RD_Y * W + i] = 255;
	for (int i = LU_Y; i < RD_Y; i++) 	Img[i * W + LU_X] = 255;
	for (int i = LU_Y; i < RD_Y; i++) 	Img[i * W + RD_X] = 255;
}

// Img: ����/���� ������ �׸� �̹����迭, W: ���� ���λ�����, H: ���� ���λ�����,
// Cx: ����/���� ������ �����Ǵ� ������ X��ǥ
// Cy: ����/���� ������ �����Ǵ� ������ Y��ǥ
void DrawCrossLine(BYTE* Img, int W, int H, int Cx, int Cy)
{
	for (int i = 0; i < W - 1; i++) // horizontal line
		Img[Cy * W + i] = 255;
	for (int i = 0; i < H - 1; i++) // vertical line
		Img[i * W + Cx] = 255;
}

void Obtain2DCenter(BYTE* Image, int W, int H, int* Cx, int* Cy)
{
	int SumX = 0, SumY = 0;
	int cnt = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (Image[i * W + j] == 0) // ���������̸�
			{
				SumX += j;
				SumY += i;
				cnt++;
			}
		}
	}
	if (cnt == 0) 	cnt = 1;
	*Cx = SumX / cnt;
	*Cy = SumY / cnt;
	//printf("%d    %d\n", Cx, Cy);
}

void Obtain2DBoundingBox(BYTE* Image, int W, int H, int* LUX, int* LUY, int* RDX, int* RDY)
{
	int flag = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (Image[i * W + j] == 0) {
				*LUY = i;
				flag = 1;
				break;
			}
		}
		if (flag == 1) break;
	}
	flag = 0;
	for (int i = H - 1; i >= 0; i--) {
		for (int j = 0; j < W; j++) {
			if (Image[i * W + j] == 0) {
				*RDY = i;
				flag = 1;
				break;
			}
		}
		if (flag == 1) break;
	}
	flag = 0;

	for (int j = 0; j < W; j++) {
		for (int i = 0; i < H; i++) {
			if (Image[i * W + j] == 0) {
				*LUX = j;
				flag = 1;
				break;
			}
		}
		if (flag == 1) break;
	}
	flag = 0;
	for (int j = W - 1; j >= 0; j--) {
		for (int i = 0; i < H; i++) {
			if (Image[i * W + j] == 0) {
				*RDX = j;
				flag = 1;
				break;
			}
		}
		if (flag == 1) break;
	}
}

void FillColor(BYTE* Image, int X, int Y, int W, int H, BYTE R, BYTE G, BYTE B)
{// x, y ��ġ�� Ư�� �������� ä��� �̰͵� �Ųٷ� �Ǿ��־ RGB -> BGR�� �Ǿ��ִ�
	Image[Y * W * 3 + X * 3] = B; // Blue ���� ���⵵ ũ��� 3���
	Image[Y * W * 3 + X * 3 + 1] = G; // Green ����
	Image[Y * W * 3 + X * 3 + 2] = R; // Red ����
}
int main()
{
	BITMAPFILEHEADER hf; // 14����Ʈ
	BITMAPINFOHEADER hInfo; // 40����Ʈ
	RGBQUAD hRGB[256]; // 1024����Ʈ
	FILE* fp;
	fp = fopen("data/tcsample2.bmp", "rb");
	if (fp == NULL) {
		printf("File not found!\n");
		return -1;
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	int ImgSize = hInfo.biWidth * hInfo.biHeight;
	int H = hInfo.biHeight, W = hInfo.biWidth;
	BYTE* Image;
	BYTE* Output;
	if (hInfo.biBitCount == 24) { // Ʈ���÷� 24bit
		Image = (BYTE*)malloc(ImgSize * 3);// 3��� ����
		Output = (BYTE*)malloc(ImgSize * 3);
		fread(Image, sizeof(BYTE), ImgSize * 3, fp);
	}
	else { // �ε���(�׷���) 8bit
		fread(hRGB, sizeof(RGBQUAD), 256, fp);
		Image = (BYTE*)malloc(ImgSize);
		Output = (BYTE*)malloc(ImgSize);
		fread(Image, sizeof(BYTE), ImgSize, fp);
	}
	fclose(fp);

	int Histo[256] = { 0 };
	int AHisto[256] = { 0 };

	// (50, 40)��ġ�� Ư�� �������� 
	/*for (int i = 0; i < W; i++) {// ���� �������� �� �׸���
		FillColor(Image, i, 200, W, H, 0, 255, 255);
	}*/

	// (50, 100) ~ (300, 400) �ڽ� ä���
	/*for (int i = 100; i <= 400; i++) {// y��ǥ
		for (int j = 50; j <= 300; j++) {// x ��ǥ
			FillColor(Image, j, i, W, H, 255, 0, 255);
		}
	}*/

	// ���� �� �����
	/*
	// �ʱ�ȭ "����(0, 0, 0)"���� ������ ���� ä���� 
	for (int i = 0; i <  H; i++) {
		for (int j = 0; j < W; j++) {
			Image[i * W * 3 + j * 3] = 0;
			Image[i * W * 3 + j * 3 + 1] = 0;
			Image[i * W * 3 + j * 3 + 2] = 0;
		}
	}
	// C[B, G, R]
	// y��ǥ ���� 0~239 (Red) 
	for (int i = 0; i < 240; i++) {
		for (int j = 0; j < W; j++) {
			Image[i*W*3 + j*3 + 2] = 255;// C[2]
		}
	}
	// y��ǥ ���� 120 ~ 359 (Green)
	for (int i = 120; i < 360; i++) {
		for (int j = 0; j < W; j++) {
			Image[i * W * 3 + j * 3 + 1] = 255;// C[1]
		}
	}
	// y��ǥ ���� 240 ~ 479 (Blue)
	for (int i = 240; i < 480; i++) {
		for (int j = 0; j < W; j++) {
			Image[i * W * 3 + j * 3 + 0] = 255;// C[0] 
		}
	}
	*/

	// �׶��̼� ����� (B ~ R)
	double wt;// ����ġ�� ����
	for (int a = 0; a < 160; a++) {// y��ǥ
		for (int i = 0; i < W; i++) {// x��ǥ
			wt = i / (double)(W - 1);// 0~1
			Image[a * W * 3 + i * 3] = (BYTE)(255 * (1.0 - wt));  // Blue
			Image[a * W * 3 + i * 3 + 1] = (BYTE)(255 * wt); // Green
			Image[a * W * 3 + i * 3 + 2] = (BYTE)(255 * wt); // Red
		}
	}
	for (int a = 160; a < 320; a++) {// y��ǥ
		for (int i = 0; i < W; i++) {// x��ǥ
			wt = i / (double)(W - 1);// 0~1
			Image[a * W * 3 + i * 3] = (BYTE)(255 * wt);  // Blue
			Image[a * W * 3 + i * 3 + 1] = (BYTE)(255 * (1.0-wt)); // Green
			Image[a * W * 3 + i * 3 + 2] = (BYTE)(255 * wt); // Red
		}
	}
	for (int a = 320; a < 480; a++) {// y��ǥ
		for (int i = 0; i < W; i++) {// x��ǥ
			wt = i / (double)(W - 1);// 0~1
			Image[a * W * 3 + i * 3] = (BYTE)(255 * wt);  // Blue
			Image[a * W * 3 + i * 3 + 1] = (BYTE)(255 * wt); // Green
			Image[a * W * 3 + i * 3 + 2] = (BYTE)(255 * (1.0-wt)); // Red
		}
	}

	SaveBMPFile(hf, hInfo, hRGB, Image, hInfo.biWidth, hInfo.biHeight, "data/output.bmp");

	free(Image);
	free(Output);
	//free(Temp);
	return 0;
}