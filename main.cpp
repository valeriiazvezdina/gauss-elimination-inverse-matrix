#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int N = 3; // dimension of the original matrix

float getNum() // input by one
{
    float n;
    cin >> n;
    return n;
}

void printMatrix(float** m, int k) // printing the matrix that is depend on the length of the matrix
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < k; j++)
        {
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

float** initMatrix() // inicialization the matrix like an array of array
{
    float** m = new float*[20];

    for (int i = 0; i < N; i++)
    {
        m[i] = new float[20];
    }

    return m;
}

float** getMatrix() // user's input of whole matrix
{
    float** m = initMatrix();

    cout << "enter the numbers of matrix row by row: " << endl;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << "enter the ";
            cout << (j + 1);
            cout << " element of ";
            cout << (i + 1);
            cout << " row:" << endl;
            m[i][j] = getNum();
        }
    }

    return m;
}

void swapRows(float** m) // ascending swapping rows of the matrix depending on the first element of the row
{
    for (int i = N - 1; i > 0; i--)
    {
        if (m[i - 1][0] < m[i][0])
        {
            float* temp = m[i];
            m[i] = m[i - 1];
            m[i - 1] = temp;
        }
    }
}

float** getAugmentedMatrix(float** m) // creating of the augmented matrix using the original matrix and identity matrix
{
    float** aug = initMatrix();

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N * 2; j++)
        {
            if (j < N)
            {
                aug[i][j] = m[i][j]; // the first part of the augmented matrix is the original matrix we have
            }
            else if ((j - i) == N)
            {
                aug[i][j] = 1; // identity matrix which has 1 on the diagonal
            }
            else
            {
                aug[i][j] = 0;
            }
        }
        cout << endl;
    }
    return aug;
}

void gaussElimination(float** m) // the main function for the elimination
{
    float d; // like delta that means the difference between some elements of the matrix

    for (int i = 0; i < N; i++)
    {
        if (m[i][i] == 0) swapRows(m); // in case the first element is equal to 0

        for (int j = 0; j < N; j++)
        {
            if (i != j)
            {
                d = m[j][i] / m[i][i]; // calculating this delta

                for (int k = 0; k < N * 2; k++)
                {
                    m[j][k] = m[j][k] - d * m[i][k]; // and using the delta for making 0 from the element
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        float temp = m[i][i];
        for (int j = 0; j < N * 2; j++)
        {
            m[i][j] = m[i][j] / temp; // making 1 on the diagonal
        }
    }
}

void printInverseMatrix(float** m) // printing the inverse matrix, it has the own function,
{
    for (int i = 0; i < N; i++)
    {
        for (int j = N; j < 2 * N; j++) // because of that moment, where just from N-ths element printing starts
        {
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    cout<< setprecision(2) << fixed; // precision for the float values

    float** A = getMatrix(); // original matrix

    float** augA = getAugmentedMatrix(A); // augmented matrix

    // common input
    cout << "======= original matrix =======" << endl;
    printMatrix(A, N);

    cout << "======= augmented matrix =======" << endl;
    printMatrix(augA, N * 2);

    gaussElimination(augA); // making the elimination

    cout << "=== augmented matrix after elimination ===" << endl;
    printMatrix(augA, N * 2);

    cout << "======= inversed matrix =======" << endl;
    printInverseMatrix(augA);

    // preventing from leaking the memory
    delete[] augA;
    delete[] A;

    return 0;
}
