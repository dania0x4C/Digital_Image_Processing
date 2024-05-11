#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
int main()
{
    BITMAPFILEHEADER hf;    // 14bite
    BITMAPINFOHEADER hInfo; // 40bite
    RGBQUAD hRGB[256];      // 1024bite
    FILE* fp;

    fp = fopen("data/lenna.bmp", "rb");

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

    for (int i = 0; i < ImgSize; i++)
    {
        Output[i] = Image[i];
    }

    fp = fopen("data/output1.bmp", "wb");
    fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp); // ����Ҷ��� 1bite ������ �����ϱ�
    fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(Output, sizeof(BYTE), ImgSize, fp);
    fclose(fp);

    for (int i = 0; i < ImgSize; i++)
    {
        Output[i] = Image[i] + 50 ;
    }

    fp = fopen("data/output2.bmp", "wb");
    fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp); // ����Ҷ��� 1bite ������ �����ϱ�
    fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(Output, sizeof(BYTE), ImgSize, fp);
    fclose(fp);

    for (int i = 0; i < ImgSize; i++)
    {
        Output[i] = 255 - Image[i];
    }

    fp = fopen("data/output3.bmp", "wb");
    fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp); // ����Ҷ��� 1bite ������ �����ϱ�
    fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(Output, sizeof(BYTE), ImgSize, fp);
    fclose(fp);
    free(Image);
    free(Output); // �����Ҵ� free ���ֱ�  - memory lick�� ���� �� �ֱ� ������ �� �ؾ��Ѵ�



    return 0;
}