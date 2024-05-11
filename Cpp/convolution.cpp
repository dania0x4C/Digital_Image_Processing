#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void AverageConv(BYTE* Img, BYTE* Out, int W, int H)// (x,y)�� ǥ���ϴ� ��� [i*W + j]
{
    double Kernel[3][3] = {0.11111, 0.11111, 0.11111,
                            0.11111, 0.11111, 0.11111,
                            0.11111, 0.11111, 0.11111 };

    double SumProduct = 0.0;
    for (int i = 1; i < H-1; i++) {//Y��ǥ(��)//�� ���� �� ���� �ϱ��  �� ĭ�� ���ΰ�
        for (int j = 1; j < W-1; j++) {//X��ǥ(��)
            for (int m = -1; m <= 1;m++) {//Kernel Y��ǥ(��) Ŀ�� �� �� 9���� ��Ÿ���� for��
                for (int n = -1; n <= 1;n++) {//Kernel X��ǥ(��)
                    SumProduct += Img[(i+m) * W + (j+n)] * Kernel[m+1][n+1];//�迭���� ������ X �׷��� +1�� ����
                }
            }
            Out[i * W + j] = (BYTE)SumProduct;
            SumProduct = 0.0;
        }
    }
}

void GaussAvrConv(BYTE* Img, BYTE* Out, int W, int H) 
{
    double Kernel[3][3] = { 0.0625, 0.125, 0.0625,
                            0.125, 0.25, 0.125,
                            0.0625, 0.125, 0.0625 };

    double SumProduct = 0.0;
    for (int i = 1; i < H - 1; i++) {//Y��ǥ(��)//�� ���� �� ���� �ϱ��  �� ĭ�� ���ΰ�
        for (int j = 1; j < W - 1; j++) {//X��ǥ(��)
            for (int m = -1; m <= 1;m++) {//Kernel Y��ǥ(��) Ŀ�� �� �� 9���� ��Ÿ���� for��
                for (int n = -1; n <= 1;n++) {//Kernel X��ǥ(��)
                    SumProduct += Img[(i + m) * W + (j + n)] * Kernel[m + 1][n + 1];//�迭���� ������ X �׷��� +1�� ����
                }
            }
            Out[i * W + j] = (BYTE)SumProduct;
            SumProduct = 0.0;
        }
    }
}

void Prewitt_X_Conv(BYTE* Img, BYTE* Out, int W, int H)//  ����� ���� ���� ������ ���� �����ؼ� �������� ��ȯ �ؾߵ�
{
    double Kernel[3][3] = { -1.0, 0.0, 1.0,
                            -1.0, 0.0, 1.0,
                            -1.0, 0.0, 1.0 };

    double SumProduct = 0.0;
    for (int i = 1; i < H - 1; i++) {//Y��ǥ(��)//�� ���� �� ���� �ϱ��  �� ĭ�� ���ΰ�
        for (int j = 1; j < W - 1; j++) {//X��ǥ(��)
            for (int m = -1; m <= 1;m++) {//Kernel Y��ǥ(��) Ŀ�� �� �� 9���� ��Ÿ���� for��
                for (int n = -1; n <= 1;n++) {//Kernel X��ǥ(��)
                    SumProduct += Img[(i + m) * W + (j + n)] * Kernel[m + 1][n + 1];//�迭���� ������ X �׷��� +1�� ����
                }
            }
            //0~755 ===> 0~255
            
            Out[i * W + j] = abs((long)SumProduct) / 3;
            SumProduct = 0.0;
        }
    }
}

void Prewitt_Y_Conv(BYTE* Img, BYTE* Out, int W, int H)//  ����� ���� ���� ������ ���� �����ؼ� �������� ��ȯ �ؾߵ�
{
    double Kernel[3][3] = { -1.0, -1.0, -1.0,
                            0.0, 0.0, 0.0,
                            1.0, 1.0, 1.0 };

    double SumProduct = 0.0;
    for (int i = 1; i < H - 1; i++) {//Y��ǥ(��)//�� ���� �� ���� �ϱ��  �� ĭ�� ���ΰ�
        for (int j = 1; j < W - 1; j++) {//X��ǥ(��)
            for (int m = -1; m <= 1;m++) {//Kernel Y��ǥ(��) Ŀ�� �� �� 9���� ��Ÿ���� for��
                for (int n = -1; n <= 1;n++) {//Kernel X��ǥ(��)
                    SumProduct += Img[(i + m) * W + (j + n)] * Kernel[m + 1][n + 1];//�迭���� ������ X �׷��� +1�� ����
                }
            }
            //0~755 ===> 0~255

            Out[i * W + j] = abs((long)SumProduct) / 3;
            SumProduct = 0.0;
        }
    }
}

void Sobel_X_Conv(BYTE* Img, BYTE* Out, int W, int H)//  ����� ���� ���� ������ ���� �����ؼ� �������� ��ȯ �ؾߵ�
{
    double Kernel[3][3] = { -1.0, 0.0, 1.0,
                            -2.0, 0.0, 2.0,
                            -1.0, 0.0, 1.0 };

    double SumProduct = 0.0;
    for (int i = 1; i < H - 1; i++) {//Y��ǥ(��)//�� ���� �� ���� �ϱ��  �� ĭ�� ���ΰ�
        for (int j = 1; j < W - 1; j++) {//X��ǥ(��)
            for (int m = -1; m <= 1;m++) {//Kernel Y��ǥ(��) Ŀ�� �� �� 9���� ��Ÿ���� for��
                for (int n = -1; n <= 1;n++) {//Kernel X��ǥ(��)
                    SumProduct += Img[(i + m) * W + (j + n)] * Kernel[m + 1][n + 1];//�迭���� ������ X �׷��� +1�� ����
                }
            }
            //0~1020 ===> 0~255

            Out[i * W + j] = abs((long)SumProduct) / 4;
            SumProduct = 0.0;
        }
    }
}

void Sobel_Y_Conv(BYTE* Img, BYTE* Out, int W, int H)//  ����� ���� ���� ������ ���� �����ؼ� �������� ��ȯ �ؾߵ�
{
    double Kernel[3][3] = { -1.0, -2.0, -1.0,
                            0.0, 0.0, 0.0,
                            1.0, 2.0, 1.0 };

    double SumProduct = 0.0;
    for (int i = 1; i < H - 1; i++) {//Y��ǥ(��)//�� ���� �� ���� �ϱ��  �� ĭ�� ���ΰ�
        for (int j = 1; j < W - 1; j++) {//X��ǥ(��)
            for (int m = -1; m <= 1;m++) {//Kernel Y��ǥ(��) Ŀ�� �� �� 9���� ��Ÿ���� for��
                for (int n = -1; n <= 1;n++) {//Kernel X��ǥ(��)
                    SumProduct += Img[(i + m) * W + (j + n)] * Kernel[m + 1][n + 1];//�迭���� ������ X �׷��� +1�� ����
                }
            }
            //0~1020 ===> 0~255

            Out[i * W + j] = abs((long)SumProduct) / 4;
            SumProduct = 0.0;
        }
    }
}

void Laplace_Conv(BYTE* Img, BYTE* Out, int W, int H)//  ����� ���� ���� ������ ���� �����ؼ� �������� ��ȯ �ؾߵ�
{
    double Kernel[3][3] = { -1.0, -1.0, -1.0,
                            -1.0, 8.0, -1.0,
                            -1.0, -1.0, 11.0 };

    double SumProduct = 0.0;
    for (int i = 1; i < H - 1; i++) {//Y��ǥ(��)//�� ���� �� ���� �ϱ��  �� ĭ�� ���ΰ�
        for (int j = 1; j < W - 1; j++) {//X��ǥ(��)
            for (int m = -1; m <= 1;m++) {//Kernel Y��ǥ(��) Ŀ�� �� �� 9���� ��Ÿ���� for��
                for (int n = -1; n <= 1;n++) {//Kernel X��ǥ(��)
                    SumProduct += Img[(i + m) * W + (j + n)] * Kernel[m + 1][n + 1];//�迭���� ������ X �׷��� +1�� ����
                }
            }
            //0~2040 ===> 0~255

            Out[i * W + j] = abs((long)SumProduct) / 8;
            SumProduct = 0.0;
        }
    }
}

void Laplace_Conv_DC(BYTE* Img, BYTE* Out, int W, int H)// ��� ����
{
    double Kernel[3][3] = { -1.0, -1.0, -1.0,
                            -1.0, 9.0, -1.0,
                            -1.0, -1.0, 11.0 };

    double SumProduct = 0.0;
    for (int i = 1; i < H - 1; i++) {//Y��ǥ(��)//�� ���� �� ���� �ϱ��  �� ĭ�� ���ΰ�
        for (int j = 1; j < W - 1; j++) {//X��ǥ(��)
            for (int m = -1; m <= 1;m++) {//Kernel Y��ǥ(��) Ŀ�� �� �� 9���� ��Ÿ���� for��
                for (int n = -1; n <= 1;n++) {//Kernel X��ǥ(��)
                    SumProduct += Img[(i + m) * W + (j + n)] * Kernel[m + 1][n + 1];//�迭���� ������ X �׷��� +1�� ����
                }
            }
            //0~2040 ===> 0~255

            //Out[i * W + j] = abs((long)SumProduct) / 8;

            //����� clippingó��
            if ((long)SumProduct > 255.0) {
                Out[i * W + j] = 255;
            }
            else if (SumProduct < 0.0) {
                Out[i * W + j] = 0;
            }
            else {
                Out[i * W + j] = (BYTE)SumProduct;
            }
            SumProduct = 0.0;
        }
    }
}

int main()
{
    BITMAPFILEHEADER hf;    // 14bite
    BITMAPINFOHEADER hInfo; // 40bite
    RGBQUAD hRGB[256];      // 1024bite
    FILE* fp;

    fp = fopen("data/LENNA.bmp", "rb");

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
    BYTE* Temp = (BYTE*)malloc(ImgSize);
    // BYTE Image[ImageSize] �̷� �ǹ̷� �����ϸ� ��
    BYTE* Output = (BYTE*)malloc(ImgSize);
    fread(Image, sizeof(BYTE), ImgSize, fp); // �̹����� ȭ������
    fclose(fp);

    int Histo[256] = { 0 };// �� ȭ�Һ� ������ �迭�� �߰���
    int AHisto[256] = { 0 };// ���� ������ ��
    //ObtainHistogram(Image, Histo, hInfo.biWidth, hInfo.biHeight);

    //int Thres = GonzalezBinThresh(Image, Output, hInfo.biWidth, hInfo.biHeight, Histo);

    //Binarization(Image, Output, hInfo.biWidth, hInfo.biHeight, Thres);

    //AverageConv(Image, Output, hInfo.biWidth, hInfo.biHeight);


    //GaussAvrConv(Image, Output, hInfo.biWidth, hInfo.biHeight);//center�� ���� �� �ִ� ���� ������ ���� ������ �� �����ϰڴٴ� �ǹ� 

    // X������ �ϰ� ����ȭ
    Prewitt_X_Conv(Image, Output, hInfo.biWidth, hInfo.biHeight);
    //Binarization(Output, Output, hInfo.biWidth, hInfo.biHeight, 50);// prewittX �� ���� ����ȭ �ϴ� ���
    

    //Prewitt_Y_Conv(Image, Output, hInfo.biWidth, hInfo.biHeight);

    /*//X,Y���� ��� �Ѵ� ��ħ
    Prewitt_X_Conv(Image, Temp, hInfo.biWidth, hInfo.biHeight);
    Prewitt_Y_Conv(Image, Output, hInfo.biWidth, hInfo.biHeight);
    for (int i = 0; i < ImgSize;i++) {
        if (Temp[i] > Output[i]) {
            Output[i] = Temp[i];
        }
    }
    */

    //Sobel_X_Conv(Image, Output, hInfo.biWidth, hInfo.biHeight);// ��踦 �� �����ϰ� ������ش�
    
    //�ڱ��ڱ� ������� ����þ��� ���� �ؼ� ������ ��
    //Laplace_Conv(Image, Output, hInfo.biWidth, hInfo.biHeight);
  
    //Laplace_Conv_DC(Image, Output, hInfo.biWidth, hInfo.biHeight);
    
    
    fp = fopen("data/output.bmp", "wb");
    fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp); // ����Ҷ��� 1bite ������ �����ϱ�
    fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(Output, sizeof(BYTE), ImgSize, fp);
    fclose(fp);
    free(Image);
    free(Temp);
    free(Output);
    return 0;
}


