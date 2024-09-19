#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    float nota_media, horas_estudo_semanais;
    int rotulo; // 0 - não foi aprovado, 1 - foi aprovado
    float distancia;
} Estudante;

typedef struct
{
    float nota_media, horas_estudo_semanais;
    int rotulo;
} Amostra;

typedef struct
{
    float distancia;
    int rotulo;
} Distancia;

float distanciaEuclidiana(Amostra a, Estudante e)
{
    float dif_nota = a.nota_media - e.nota_media;
    float dif_horas = a.horas_estudo_semanais - e.horas_estudo_semanais;
    return sqrt(dif_nota * dif_nota + dif_horas * dif_horas);
}

void merge(Distancia vetor[], Distancia aux[], int imin, int imid, int imax)
{
    int i = imin, j = imid + 1;
    for (int k = imin; k <= imax; k++)
        aux[k] = vetor[k];
    for (int k = imin; k <= imax; k++)
        if (i > imid)
            vetor[k] = aux[j++];
        else if (j > imax)
            vetor[k] = aux[i++];
        else if (aux[j].distancia < aux[i].distancia)
            vetor[k] = aux[j++];
        else
            vetor[k] = aux[i++];
}

void mergeSort(Distancia vetor[], Distancia aux[], int imin, int imax)
{
    if (imin < imax)
    {
        int imid = (imin + imax) / 2;
        mergeSort(vetor, aux, imin, imid);
        mergeSort(vetor, aux, imid + 1, imax);
        merge(vetor, aux, imin, imid, imax);
    }
}

int main()
{
    unsigned m, n, k;

    scanf("%u %u %u", &m, &n, &k);

    Estudante *estudantes = malloc(m * sizeof(Estudante));
    Amostra *amostras = malloc(n * sizeof(Amostra));

    for (unsigned i = 0; i < m; i++)
    {
        scanf("%f %f %d", &estudantes[i].nota_media, &estudantes[i].horas_estudo_semanais, &estudantes[i].rotulo);
    }

    for (unsigned i = 0; i < n; i++)
    {
        scanf("%f %f", &amostras[i].nota_media, &amostras[i].horas_estudo_semanais);
    }

    for (unsigned i = 0; i < n; i++)
    {
        Distancia *distancias = malloc(k * sizeof(Distancia));
        int cont = 0;

        for (unsigned j = 0; j < k; j++)
        {
            distancias[j].distancia = distanciaEuclidiana(amostras[i], estudantes[j]);
            distancias[j].rotulo = estudantes[j].rotulo;
            if (estudantes[j].rotulo)
                cont++;
        }

        Distancia *aux = malloc(k * sizeof(Distancia));
        mergeSort(distancias, aux, 0, k - 1);
        free(aux);

        for (unsigned j = k; j < m; j++)
        {
            float aux_dist = distanciaEuclidiana(amostras[i], estudantes[j]);

            if (aux_dist < distancias[k - 1].distancia)
            {
                if (distancias[k - 1].rotulo)
                    cont--;
                if (estudantes[j].rotulo)
                    cont++;

                distancias[k - 1].distancia = aux_dist;
                distancias[k - 1].rotulo = estudantes[j].rotulo;

                mergeSort(distancias, aux, 0, k - 1);
            }
        }

        if (cont > ((int)k/2))
        {
            printf("Aluno %u: (%.2f, %.2f) = Aprovado\n", i, amostras[i].nota_media, amostras[i].horas_estudo_semanais);
        }
        else
        {
            printf("Aluno %u: (%.2f, %.2f) = Reprovado\n", i, amostras[i].nota_media, amostras[i].horas_estudo_semanais);
        }

        free(distancias);
    }

    free(estudantes);
    free(amostras);

    return 0;
}
