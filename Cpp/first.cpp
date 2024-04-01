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

    fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp); // 현재 파일포인터에서 한 번 읽어온다
    fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
    fread(hRGB, sizeof(RGBQUAD), 256, fp);

    int ImgSize = hInfo.biWidth * hInfo.biHeight;

    BYTE* Image = (BYTE*)malloc(ImgSize); // 동적 할당(0~255)
    // BYTE Image[ImageSize] 이런 의미로 생각하면 됨
    BYTE* Output = (BYTE*)malloc(ImgSize);
    fread(Image, sizeof(BYTE), ImgSize, fp); // 이미지의 화소정보
    fclose(fp);

    for (int i = 0; i < ImgSize; i++)
    {
        Output[i] = Image[i];
    }

    fp = fopen("data/output1.bmp", "wb");
    fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp); // 기록할때는 1bite 단위로 저장하기
    fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(Output, sizeof(BYTE), ImgSize, fp);
    fclose(fp);

    for (int i = 0; i < ImgSize; i++)
    {
        Output[i] = Image[i] + 50 ;
    }

    fp = fopen("data/output2.bmp", "wb");
    fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp); // 기록할때는 1bite 단위로 저장하기
    fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(Output, sizeof(BYTE), ImgSize, fp);
    fclose(fp);

    for (int i = 0; i < ImgSize; i++)
    {
        Output[i] = 255 - Image[i];
    }

    fp = fopen("data/output3.bmp", "wb");
    fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp); // 기록할때는 1bite 단위로 저장하기
    fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(Output, sizeof(BYTE), ImgSize, fp);
    fclose(fp);
    free(Image);
    free(Output); // 동적할당 free 해주기  - memory lick을 당할 수 있기 때문에 꼭 해야한다



    return 0;
}