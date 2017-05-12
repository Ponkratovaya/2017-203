#include "ponkratovayv.h"

/**
 * Метод Гаусса
 */
void ponkratovayv::lab1()
{
double d ;
    //прямой ход
    for (int k = 0; k < N; k++)
    {
        d = A[k][k];
        for (int j = 0; j < N; j++)
            A[k][j] = A[k][j]/ d;
        b[k] = b[k]/d;

        for (int i = k + 1; i < N; i++)
        {
            d = A[i][k];
            for (int j = 0; j < N; j++)
            {
                A[i][j] = A[i][j]-A[k][j] * d;
            }
            b[i] =b[i]- b[k] * d;
        }
    }

    //обратный ход
    for (int k = N - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            d = A[i][k];
            for (int j = 0; j < N; j++)
                A[i][j] =A[i][j]- A[k][j] *d;
            b[i] =b[i]- b[k] * d;
        }
    }

    for(int i=0; i<N; i++)
        x[i]=b[i];
    cout << "Hello world!" << endl;
    return 0;
}
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void ponkratovayv::lab2()
{
 double d;
    //прямой ход
    for (int k = 0; k < N; k++)
    {
        int maxx=k;
        for(int i=k+1;i<N;i++)
            if(abs(A[i][k]) > abs(A[maxx][k]))
                maxx=i;
        for(int i=0;i<N;i++)
            swap(A[k][i],A[maxx][i]);
        swap(b[k],b[maxx]);
        d = A[k][k];
        for (int j = 0; j < N; j++)
            A[k][j] = A[k][j]/d;
        b[k] =b[k]/ d;
        for (int i = k + 1; i < N; i++)
        {
            d = A[i][k];
            for (int j = 0; j < N; j++)
            {
                A[i][j] =A[i][j]- A[k][j] * d;
            }
            b[i] =b[i]- b[k] * d;
        }
    }
    //обратный ход
    for (int k = N - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            d = A[i][k];
            for (int j = 0; j < N; j++)
                A[i][j] =A[i][j]- A[k][j] * d;
            b[i] =b[i]- b[k] * d;
        }
    }

    for(int i=0; i<N; i++)
        x[i]=b[i];
    cout << "Hello world!" << endl;
    return 0;
}
std::string ponkratovayv::get_name()
{
  return std::string("Понкратова Юлия");
}


/**
 * Метод квадратного корня (метод Холецкого)
 */
void ponkratovayv::lab3()
{

}



/**
 * Метод прогонки
 */
void ponkratovayv::lab4()
{
double *alpha = new double[N];
    double *beta = new double[N];

    //определяем прогоночные коэффициенты
    alpha[1] = -A[0][1] / A[0][0];
    beta[1] = b[0] / A[0][0];
    for(int i=2; i<N; i++)
    {
        double a = A[i-1][i-2]; //эл-т под диагональю
        double c = -A[i-1][i-1]; //эл-т диагонали
        double e = A[i-1][i]; //эл-т над диагональю

        alpha[i] = e / (c - a * alpha[i-1]);
        beta[i] = (a * beta[i-1] - b[i-1]) / (c - a * alpha[i-1]);
    }

    x[N-1] = (A[N-1][N-2] * beta[N-1] - b[N-1]) / (-A[N-1][N-1] - alpha[N-1] * A[N-1][N-2]);

    for(int i=N-2; i>=0; i--)
    {
        x[i] = alpha[i+1] * x[i+1] + beta[i+1];
    }

    delete [] alpha;
    delete [] beta;
}



/**
 * Метод Якоби
 */
void ponkratovayv::lab5()
{
   double *alt = new double[N];
    for (int i=0; i<N; i++)
    {
        x[i]=0; // начальное приближение
    }
    double error=0.0;
    double eps=0.000001;
    int k=0;
    do
    {
        k++;
        error=0.0;
        for(int i=0; i<N; i++)
            alt[i]=x[i];
        for(int i=0; i<N; i++)
        {
            double s=0;
            for(int j=0; j<i; j++)
                s += A[i][j] * alt[j];

            for(int j=i+1; j<N; j++)
                s += A[i][j] * alt[j];
            x[i]=(b[i] - s)/A[i][i];
        }
        error = std::abs(alt[0]-x[0]);
        for(int i=0; i<N; i++)
        {
            if(std::abs(xold[i]-x[i]) > error)
                error = std::abs(xold[i]-x[i]);
        }
    } while(error >= eps);
    std::cout << "Чило итераций : " << k << std::endl;

    delete [] xold;
}



/**
 * Метод Зейделя
 */
void ponkratovayv::lab6()
{
double *alt = new double[N];
    for (int i=0; i<N; i++)
    {
        x[i]=0; // начальное приближение
    }
    double error=0.0;
    double eps=0.000001;
    int k=0;
    do
    {
        k++;
        error=0.0;
        for(int i=0; i<N; i++)
            alt[i]=x[i];
        for(int i=0; i<N; i++)
        {
            double s=0;
            for(int j=0; j<i; j++)
                s += A[i][j] * x[j];
            for(int j=i+1; j<N; j++)
                s += A[i][j] * alt[j];
            x[i]=(b[i] - s)/A[i][i];
        }
        for(int i=0; i<N; i++)
        {
            if(std::abs(alt[i]-x[i]) > error)
                error = std::abs(alt[i]-x[i]);
        }

    } 
    while(error >= eps);
    std::cout << "Чило итераций : " << k << std::endl;

    delete [] xold;
}



/**
 * Один из градиентных методов
 */
void ponkratovayv::lab7()
{

}
void ponkratovayv::lab8()
{

}
