#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void InverseImage(BYTE* Img, BYTE* Out, int W, int H) 
{
    int ImgSize = W * H;

    for (int i = 0; i < ImgSize; i++)
    {
        Out[i] = 255 - Img[i];
    }
}

void BrightnessAdj(BYTE* Img, BYTE* Out, int W, int H, int Val)
{
    int ImgSize = W * H;

    for (int i = 0; i < ImgSize; i++)
    {
        if (Img[i] + Val > 255) 
        {
            Out[i] = 255;
        }
        else if (Img[i] + Val < 0) 
        {
            Out[i] = 0;
        }
        else 
        {
            Out[i] = Img[i] + Val;
        }
        
    }
}

void ContrastAdj(BYTE* Img, BYTE* Out, int W, int H, double Val)
{
    int ImgSize = W * H;

    for (int i = 0; i < ImgSize; i++)
    {
        if (Img[i] * Val > 255.0)
        {
            Out[i] = 255;
        }
        else
        {
            Out[i] = (BYTE)(Img[i] * Val);//byte * double = double 그래서 강제 형 변환
        }

    }
}

void ObtainHistogram(BYTE* Img, int* Histo, int W, int H) {
    int ImgSize = W * H;
    

    for (int i = 0;i < ImgSize;i++)
    {
        Histo[Img[i]]++;// 이미지에 해당하는 화소 값이 있는데 그것에 대한 index값을 증가 시킴
    }
}

void HistogramStretching(BYTE* Img, BYTE* Out, int* Histo, int W, int H) {
    // 스트래칭 방식
    int ImgSize = W * H;

    BYTE Low = 0, High = 0;

    for (int i = 0;i < 256;i++)
    {
        //if (Image[i] < Low) {
        //    Low = Image[i];
        //}
        if (Histo[i] != 0) {
            Low = i;
            break;
        }
    }

    for (int i = 255;i >= 0;i--)
    {
        if (Histo[i] != 0) {
            High = i;
            break;
        }
    }

    for (int i = 0;i < ImgSize;i++) {
        Out[i] = (BYTE)(Img[i] - Low) / (double)(High - Low) * 255.0;// Byte = 0 or 1 그렇기 때문에 나누면 0 or 1 그래서 double로 형 변환
    }
}

void ObtainAHistogram(int* Histo, int* AHisto) 
{
    for (int i = 0; i < 256; i++) 
    {
        for (int j = 0; j <= i; j++) 
        {
            AHisto[i] += Histo[j];
        }
    }
}

void HistogramEqualization(BYTE* Img, BYTE* Out, int* AHisto, int W, int H) {
    int ImgSize = W * H;

    int Nt = W * H;
    int Gmax = 255;// 영상이 가질 수 있는 최대밝기
    double Ratio = Gmax / (double)Nt;
    BYTE NormSum[256];// 정규화
    for (int i = 0;i < 256;i++) {
        NormSum[i] = (BYTE)(Ratio * AHisto[i]);
    }
    for (int i = 0; i < ImgSize; i++)
    {
        Out[i] = NormSum[Img[i]];
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

        for (int i = 0; i < T+1; i++) {
            Cnt1 += Histo[i];
            Sum1 += i * Histo[i];
        }
        int M1 = Sum1 / Cnt1;

        int Cnt2 = 0, Sum2 = 0;

        for (int i = T + 1; i < 256; i++) {
            Cnt2 += Histo[i];
            Sum2 += i * Histo[i];
        }
        int M2 = (Cnt2 == 0) ? 0 : Sum2 / Cnt2;

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

    fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp); // 현재 파일포인터에서 한 번 읽어온다
    fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
    fread(hRGB, sizeof(RGBQUAD), 256, fp);

    int ImgSize = hInfo.biWidth * hInfo.biHeight;

    BYTE* Image = (BYTE*)malloc(ImgSize); // 동적 할당(0~255)
    // BYTE Image[ImageSize] 이런 의미로 생각하면 됨
    BYTE* Output = (BYTE*)malloc(ImgSize);
    fread(Image, sizeof(BYTE), ImgSize, fp); // 이미지의 화소정보
    fclose(fp);

    
    
    //InverseImage(Image, Output, hInfo.biWidth, hInfo.biHeight);

    //BrightnessAdj(Image, Output, hInfo.biWidth, hInfo.biHeight, 70);

    //ContrastAdj(Image, Output, hInfo.biWidth, hInfo.biHeight, 1.5);

    int Histo[256] = { 0 };// 각 화소별 갯수를 배열에 추가함
    int AHisto[256] = { 0 };// 누적 히스토 값

    ObtainHistogram(Image, Histo, hInfo.biWidth, hInfo.biHeight);// 히스토그램
    
    ObtainAHistogram(Histo, AHisto);// 누적 히스토그램
     
    //HistogramStretching(Image, Output, Histo, hInfo.biWidth, hInfo.biHeight);
    
    //HistogramEqualization(Image, Output, AHisto, hInfo.biWidth, hInfo.biHeight);
    int Thres = GonzalezBinThresh(Image, Output, hInfo.biWidth, hInfo.biHeight, Histo);

    Binarization(Image, Output, hInfo.biWidth, hInfo.biHeight, Thres);

    fp = fopen("data/outputB.bmp", "wb");
    fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp); // 기록할때는 1bite 단위로 저장하기
    fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(Output, sizeof(BYTE), ImgSize, fp);
    fclose(fp);
    free(Image);
    free(Output);
    return 0;
}