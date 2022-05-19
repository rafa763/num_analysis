#include <iostream>
#include<iomanip>
#include<cmath>

using namespace std;

int main()
{
    // Prompt user for options
    int choice;
    cout<<"1-polynomial \n";
    cout<<"2-exponential \n";
    cout<<"3-type y=ax^b \n";

    // Ensure valid input
    do
    {
        cout<< "Ans: ";
        cin>> choice;
    }
    while (choice < 1 || choice > 3);

    int PREC;
    cout<<"precision?\n";
    cin>>PREC;

    int i, j, k, n, N;
    double sumX=0, sumX2=0, sumY=0, sumXY=0;
    cout.precision(PREC);
    cout.setf(ios::fixed);

    // Number of x, y pairs
    cout<<"number of sets?\n";
    cin>>N;

    // array to hold x and y values
    double x[N],y[N];

    // insert x's in the array
    for (i = 0; i < N; i++)
    {
        cout<<"x[" <<i <<"]: ";
        cin>>x[i];
    }

    // insert y's in the array
    for (i = 0; i < N; i++)
    {
        cout<<"y[" <<i <<"]: ";
        cin>>y[i];
    }

    // Polynomial
    if (choice == 1)
    {

        cout<<"\nPolynomial degree?\n";
        cin>>n;

        double X[2*n+1];
        for (i = 0; i < 2*n+1; i++)
        {
            X[i]=0;
            for (j = 0; j < N; j++)
                X[i]+=pow(x[j],i);
        }

        double B[n+1][n+2],a[n+1];
        for (i = 0; i <= n; i++)
            for (j = 0; j <= n; j++)
                B[i][j]=X[i+j];

        double Y[n+1];
        for (i = 0; i < n+1; i++)
        {
            Y[i]=0;
            for (j = 0; j < N; j++)
                Y[i]+=pow(x[j],i)*y[j];
        }

        for (i = 0; i <= n; i++)
            B[i][n+1]=Y[i];

        n+=1;

        for (i = 0; i < n; i++)
            for (k = i+1; k < n ;k++)
                if (B[i][i] < B[k][i])
                    for (j = 0; j <= n; j++)
                    {
                        double temp=B[i][j];
                        B[i][j]=B[k][j];
                        B[k][j]=temp;
                    }

        for (i = 0; i < n-1; i++)
            for (k = i+1; k < n; k++)
                {
                    double t=B[k][i]/B[i][i];
                    for (j=0;j<=n;j++)
                        B[k][j] -= t*B[i][j];
                }

        for (i = n-1; i >= 0; i--)
            {
                a[i] = B[i][n];
                for (j = 0; j < n; j++)
                    if (j!=i)
                        a[i] -= B[i][j]*a[j];
                a[i]=a[i]/B[i][i];
            }

        cout<<"\nfitted Polynomial is :\ny=";
            for (i=0;i<n;i++)
                cout<<" + ("<<a[i]<<")"<<"x^"<<i;
            cout<<"\n";
    }
    // Exponential
    else if(choice == 2)
    {
        double lny[N],a,b,c;

        for (i=0;i<N;i++)
            lny[i]=log(y[i]);

        for (i=0;i<N;i++)
        {
            sumX += x[i];
            sumY += lny[i];
            sumX2 += pow(x[i],2);
            sumXY += x[i]*lny[i];
        }
        a=(N*sumXY-sumX*sumY)/(N*sumX2-sumX*sumX);
        b=(sumX2*sumY-sumX*sumXY)/(sumX2*N-sumX*sumX);
        c=pow(2.71828,b);

        cout<<"\nThe exponential is \ny = "<<c<<"e^"<<a<<"x\n";

    }
    else if(choice == 3)
    {
        float a, b, A;

        for(i = 0; i < N; i++)
        {
            sumX += log(x[i]);
            sumX2 += log(x[i])*log(x[i]);
            sumY += log(y[i]);
            sumXY += log(x[i])*log(y[i]);
        }

        /* Calculating A and b */
        b = (N*sumXY-sumX*sumY)/(N*sumX2-sumX*sumX);
        A = (sumY - b*sumX)/N;

        /* Transformation of A to a */
        a = exp(A);

        cout<<"\ny = "<<a<<"x^"<<b<<"\n";
    }
}
