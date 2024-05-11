#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void AverageConv(BYTE* Img, BYTE* Out, int W, int H)// (x,y)를 표현하는 방법 [i*W + j]
{
    double Kernel[3][3] = {0.11111, 0.11111, 0.11111,
                            0.11111, 0.11111, 0.11111,
                            0.11111, 0.11111, 0.11111 };

    double SumProduct = 0.0;
    for (int i = 1; i < H-1; i++) {//Y좌표(행)//끝 영역 값 지정 하기는  한 칸씩 띠어두고
        for (int j = 1; j < W-1; j++) {//X좌표(열)
            for (int m = -1; m <= 1;m++) {//Kernel Y좌표(행) 커널 안 쪽 9개의 나타내는 for문
                for (int n = -1; n <= 1;n++) {//Kernel X좌표(열)
                    SumProduct += Img[(i+m) * W + (j+n)] * Kernel[m+1][n+1];//배열에서 음수는 X 그래서 +1을 해줌
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
    for (int i = 1; i < H - 1; i++) {//Y좌표(행)//끝 영역 값 지정 하기는  한 칸씩 띠어두고
        for (int j = 1; j < W - 1; j++) {//X좌표(열)
            for (int m = -1; m <= 1;m++) {//Kernel Y좌표(행) 커널 안 쪽 9개의 나타내는 for문
                for (int n = -1; n <= 1;n++) {//Kernel X좌표(열)
                    SumProduct += Img[(i + m) * W + (j + n)] * Kernel[m + 1][n + 1];//배열에서 음수는 X 그래서 +1을 해줌
                }
            }
            Out[i * W + j] = (BYTE)SumProduct;
            SumProduct = 0.0;
        }
    }
}

void Prewitt_X_Conv(BYTE* Img, BYTE* Out, int W, int H)//  여기는 음수 값이 나오는 것을 주의해서 절댓값으로 변환 해야됨
{
    double Kernel[3][3] = { -1.0, 0.0, 1.0,
                            -1.0, 0.0, 1.0,
                            -1.0, 0.0, 1.0 };

    double SumProduct = 0.0;
    for (int i = 1; i < H - 1; i++) {//Y좌표(행)//끝 영역 값 지정 하기는  한 칸씩 띠어두고
        for (int j = 1; j < W - 1; j++) {//X좌표(열)
            for (int m = -1; m <= 1;m++) {//Kernel Y좌표(행) 커널 안 쪽 9개의 나타내는 for문
                for (int n = -1; n <= 1;n++) {//Kernel X좌표(열)
                    SumProduct += Img[(i + m) * W + (j + n)] * Kernel[m + 1][n + 1];//배열에서 음수는 X 그래서 +1을 해줌
                }
            }
            //0~755 ===> 0~255
            
            Out[i * W + j] = abs((long)SumProduct) / 3;
            SumProduct = 0.0;
        }
    }
}

void Prewitt_Y_Conv(BYTE* Img, BYTE* Out, int W, int H)//  여기는 음수 값이 나오는 것을 주의해서 절댓값으로 변환 해야됨
{
    double Kernel[3][3] = { -1.0, -1.0, -1.0,
                            0.0, 0.0, 0.0,
                            1.0, 1.0, 1.0 };

    double SumProduct = 0.0;
    for (int i = 1; i < H - 1; i++) {//Y좌표(행)//끝 영역 값 지정 하기는  한 칸씩 띠어두고
        for (int j = 1; j < W - 1; j++) {//X좌표(열)
            for (int m = -1; m <= 1;m++) {//Kernel Y좌표(행) 커널 안 쪽 9개의 나타내는 for문
                for (int n = -1; n <= 1;n++) {//Kernel X좌표(열)
                    SumProduct += Img[(i + m) * W + (j + n)] * Kernel[m + 1][n + 1];//배열에서 음수는 X 그래서 +1을 해줌
                }
            }
            //0~755 ===> 0~255

            Out[i * W + j] = abs((long)SumProduct) / 3;
            SumProduct = 0.0;
        }
    }
}

void Sobel_X_Conv(BYTE* Img, BYTE* Out, int W, int H)//  여기는 음수 값이 나오는 것을 주의해서 절댓값으로 변환 해야됨
{
    double Kernel[3][3] = { -1.0, 0.0, 1.0,
                            -2.0, 0.0, 2.0,
                            -1.0, 0.0, 1.0 };

    double SumProduct = 0.0;
    for (int i = 1; i < H - 1; i++) {//Y좌표(행)//끝 영역 값 지정 하기는  한 칸씩 띠어두고
        for (int j = 1; j < W - 1; j++) {//X좌표(열)
            for (int m = -1; m <= 1;m++) {//Kernel Y좌표(행) 커널 안 쪽 9개의 나타내는 for문
                for (int n = -1; n <= 1;n++) {//Kernel X좌표(열)
                    SumProduct += Img[(i + m) * W + (j + n)] * Kernel[m + 1][n + 1];//배열에서 음수는 X 그래서 +1을 해줌
                }
            }
            //0~1020 ===> 0~255

            Out[i * W + j] = abs((long)SumProduct) / 4;
            SumProduct = 0.0;
        }
    }
}

void Sobel_Y_Conv(BYTE* Img, BYTE* Out, int W, int H)//  여기는 음수 값이 나오는 것을 주의해서 절댓값으로 변환 해야됨
{
    double Kernel[3][3] = { -1.0, -2.0, -1.0,
                            0.0, 0.0, 0.0,
                            1.0, 2.0, 1.0 };

    double SumProduct = 0.0;
    for (int i = 1; i < H - 1; i++) {//Y좌표(행)//끝 영역 값 지정 하기는  한 칸씩 띠어두고
        for (int j = 1; j < W - 1; j++) {//X좌표(열)
            for (int m = -1; m <= 1;m++) {//Kernel Y좌표(행) 커널 안 쪽 9개의 나타내는 for문
                for (int n = -1; n <= 1;n++) {//Kernel X좌표(열)
                    SumProduct += Img[(i + m) * W + (j + n)] * Kernel[m + 1][n + 1];//배열에서 음수는 X 그래서 +1을 해줌
                }
            }
            //0~1020 ===> 0~255

            Out[i * W + j] = abs((long)SumProduct) / 4;
            SumProduct = 0.0;
        }
    }
}

void Laplace_Conv(BYTE* Img, BYTE* Out, int W, int H)//  여기는 음수 값이 나오는 것을 주의해서 절댓값으로 변환 해야됨
{
    double Kernel[3][3] = { -1.0, -1.0, -1.0,
                            -1.0, 8.0, -1.0,
                            -1.0, -1.0, 11.0 };

    double SumProduct = 0.0;
    for (int i = 1; i < H - 1; i++) {//Y좌표(행)//끝 영역 값 지정 하기는  한 칸씩 띠어두고
        for (int j = 1; j < W - 1; j++) {//X좌표(열)
            for (int m = -1; m <= 1;m++) {//Kernel Y좌표(행) 커널 안 쪽 9개의 나타내는 for문
                for (int n = -1; n <= 1;n++) {//Kernel X좌표(열)
                    SumProduct += Img[(i + m) * W + (j + n)] * Kernel[m + 1][n + 1];//배열에서 음수는 X 그래서 +1을 해줌
                }
            }
            //0~2040 ===> 0~255

            Out[i * W + j] = abs((long)SumProduct) / 8;
            SumProduct = 0.0;
        }
    }
}

void Laplace_Conv_DC(BYTE* Img, BYTE* Out, int W, int H)// 밝기 유지
{
    double Kernel[3][3] = { -1.0, -1.0, -1.0,
                            -1.0, 9.0, -1.0,
                            -1.0, -1.0, 11.0 };

    double SumProduct = 0.0;
    for (int i = 1; i < H - 1; i++) {//Y좌표(행)//끝 영역 값 지정 하기는  한 칸씩 띠어두고
        for (int j = 1; j < W - 1; j++) {//X좌표(열)
            for (int m = -1; m <= 1;m++) {//Kernel Y좌표(행) 커널 안 쪽 9개의 나타내는 for문
                for (int n = -1; n <= 1;n++) {//Kernel X좌표(열)
                    SumProduct += Img[(i + m) * W + (j + n)] * Kernel[m + 1][n + 1];//배열에서 음수는 X 그래서 +1을 해줌
                }
            }
            //0~2040 ===> 0~255

            //Out[i * W + j] = abs((long)SumProduct) / 8;

            //여기는 clipping처리
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

    fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp); // 현재 파일포인터에서 한 번 읽어온다
    fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
    fread(hRGB, sizeof(RGBQUAD), 256, fp);

    int ImgSize = hInfo.biWidth * hInfo.biHeight;

    BYTE* Image = (BYTE*)malloc(ImgSize); // 동적 할당(0~255)
    BYTE* Temp = (BYTE*)malloc(ImgSize);
    // BYTE Image[ImageSize] 이런 의미로 생각하면 됨
    BYTE* Output = (BYTE*)malloc(ImgSize);
    fread(Image, sizeof(BYTE), ImgSize, fp); // 이미지의 화소정보
    fclose(fp);

    int Histo[256] = { 0 };// 각 화소별 갯수를 배열에 추가함
    int AHisto[256] = { 0 };// 누적 히스토 값
    //ObtainHistogram(Image, Histo, hInfo.biWidth, hInfo.biHeight);

    //int Thres = GonzalezBinThresh(Image, Output, hInfo.biWidth, hInfo.biHeight, Histo);

    //Binarization(Image, Output, hInfo.biWidth, hInfo.biHeight, Thres);

    //AverageConv(Image, Output, hInfo.biWidth, hInfo.biHeight);


    //GaussAvrConv(Image, Output, hInfo.biWidth, hInfo.biHeight);//center에 값을 더 주는 것은 영상의 원래 정보를 더 유지하겠다는 의미 

    // X값으로 하고 이진화
    Prewitt_X_Conv(Image, Output, hInfo.biWidth, hInfo.biHeight);
    //Binarization(Output, Output, hInfo.biWidth, hInfo.biHeight, 50);// prewittX 한 것을 이진화 하는 방법
    

    //Prewitt_Y_Conv(Image, Output, hInfo.biWidth, hInfo.biHeight);

    /*//X,Y값의 경계 둘다 합침
    Prewitt_X_Conv(Image, Temp, hInfo.biWidth, hInfo.biHeight);
    Prewitt_Y_Conv(Image, Output, hInfo.biWidth, hInfo.biHeight);
    for (int i = 0; i < ImgSize;i++) {
        if (Temp[i] > Output[i]) {
            Output[i] = Temp[i];
        }
    }
    */

    //Sobel_X_Conv(Image, Output, hInfo.biWidth, hInfo.biHeight);// 경계를 더 샤프하게 만들어준다
    
    //자글자글 노이즈는 가우시안을 먼저 해서 없에면 됨
    //Laplace_Conv(Image, Output, hInfo.biWidth, hInfo.biHeight);
  
    //Laplace_Conv_DC(Image, Output, hInfo.biWidth, hInfo.biHeight);
    
    
    fp = fopen("data/output.bmp", "wb");
    fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp); // 기록할때는 1bite 단위로 저장하기
    fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(Output, sizeof(BYTE), ImgSize, fp);
    fclose(fp);
    free(Image);
    free(Temp);
    free(Output);
    return 0;
}


