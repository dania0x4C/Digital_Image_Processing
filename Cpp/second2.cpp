#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


void ObtainHistogram(BYTE* Img, int* Histo, int W, int H) {
    int ImgSize = W * H;


    for (int i = 0;i < ImgSize;i++)
    {
        Histo[Img[i]]++;// �̹����� �ش��ϴ� ȭ�� ���� �ִµ� �װͿ� ���� index���� ���� ��Ŵ
    }
}



void Binarization(BYTE* Img, BYTE* Out, int W, int H, BYTE Threshold) {
    int ImgSize = W * H;

    for (int i = 0;i < ImgSize;i++)
    {
        if (Img[i] < Threshold) {
            Out[i] = 0;
        }
        else {
            Out[i] = 255;
        }
    }
}

int GonzalezBinThresh(BYTE* Img, BYTE* Out, int W, int H, int* Histo)
{
    BYTE Low = 0, High = 255;

    for (int i = 0; i < 256; i++)
    {
        if (Histo[i] != 0) {
            Low = i;
            break;
        }
    }

    for (int i = 255; i >= 0; i--)
    {
        if (Histo[i] != 0) {
            High = i;
            break;
        }
    }

    int T = (Low + High) / 2;
    int T2 = 0;

    do {
        int Cnt1 = 0, Sum1 = 0;

        for (int i = 0; i < T + 1; i++) {
            Cnt1 += Histo[i];
            Sum1 += i * Histo[i];
        }
        int M1 = Sum1 / Cnt1;

        int Cnt2 = 0, Sum2 = 0;

        for (int i = T + 1; i < 256; i++) {
            Cnt2 += Histo[i];
            Sum2 += i * Histo[i];
        }
        int M2 = Sum2 / Cnt2;

        T2 = (M1 + M2) / 2;
        T = T2;

    } while (abs(T - T2) > 3);

    return T;
}

int main()
{
    BITMAPFILEHEADER hf;    // 14bite
    BITMAPINFOHEADER hInfo; // 40bite
    RGBQUAD hRGB[256];      // 1024bite
    FILE* fp;

    fp = fopen("data/coin.bmp", "rb");

    if (fp == NULL)
    {
        printf("File not found!\n");
        return -1;
    }

    fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp); // ���� ���������Ϳ��� �� �� �о�´�
    fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
    fread(hRGB, sizeof(RGBQUAD), 256, fp);

    int ImgSize = hInfo.biWidth * hInfo.biHeight;

    BYTE* Image = (BYTE*)malloc(ImgSize); // ���� �Ҵ�(0~255)
    // BYTE Image[ImageSize] �̷� �ǹ̷� �����ϸ� ��
    BYTE* Output = (BYTE*)malloc(ImgSize);
    fread(Image, sizeof(BYTE), ImgSize, fp); // �̹����� ȭ������
    fclose(fp);

    int Histo[256] = { 0 };// �� ȭ�Һ� ������ �迭�� �߰���
    int AHisto[256] = { 0 };// ���� ������ ��
    ObtainHistogram(Image, Histo, hInfo.biWidth, hInfo.biHeight);

    int Thres = GonzalezBinThresh(Image, Output, hInfo.biWidth, hInfo.biHeight, Histo);

    Binarization(Image, Output, hInfo.biWidth, hInfo.biHeight, Thres);

    fp = fopen("data/output.bmp", "wb");
    fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp); // ����Ҷ��� 1bite ������ �����ϱ�
    fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(Output, sizeof(BYTE), ImgSize, fp);
    fclose(fp);
    free(Image);
    free(Output);
    return 0;
}