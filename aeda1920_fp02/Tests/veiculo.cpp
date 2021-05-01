#include "veiculo.h"
#include <iostream>

using namespace std;

Veiculo::Veiculo(string mc, int m, int a) {
    marca=mc;
    mes=m;
    ano=a;
}

Motorizado::Motorizado(string mc, int m, int a, string c, int cil): Veiculo(mc, m, a) {
    combustivel=c;
    cilindrada=cil;
}

Automovel::Automovel(string mc, int m, int a, string c, int cil) : Motorizado(mc, m ,a ,c, cil){}

Camiao::Camiao(string mc, int m, int a, string c, int cil, int cm): Motorizado(mc, m, a, c ,cil){carga_maxima=cm;}

Bicicleta::Bicicleta(string mc, int m, int a, string t): Veiculo(mc, m , a) {tipo=t;}

string Motorizado::getCombustivel() const {return this->combustivel;}

int Motorizado::getCilindrada() const {return this->cilindrada;}

int Motorizado::info() const
{
    cout << "Ano: " << ano << endl << "Mes: " << mes << endl << "Marca: " << marca << endl << "Combustivel: " << combustivel << endl << "Cilindrada: " << cilindrada;
    return 5;
}

string Veiculo::getMarca() const {return this->marca;}

int Veiculo::getAno() const {return this-> ano;}

int Veiculo::getMes() const {return this-> mes;}

bool Veiculo::operator < (const Veiculo & v) const
{
    int dateLeft=ano*100+mes;
    int dateRight=v.getAno()*100+v.getMes();
    if(dateLeft<dateRight)
        return true;
    else
        return false;
}

int Veiculo::info() const
{
    cout << "Ano: " << ano << endl << "Mes: " << mes << endl << "Marca: " << marca;
    return 3;
}

int Automovel::info() const
{
    cout << "Ano: " << ano << endl << "Mes: " << mes << endl << "Marca: " << marca << endl << "Cilindrada: " << this->getCilindrada() << endl << "Combustivel: "<< this->getCombustivel();
    return 5;
}

int Camiao::info() const
{
    cout << "Ano: " << ano << endl << "Mes: " << mes << endl << "Marca: " << marca << endl << "Cilindrada: " << this->getCilindrada() << endl << "Combustivel: "<< this->getCombustivel() << endl << "Carga Maxima: " << carga_maxima;
    return 6;
}

int Bicicleta::info() const
{
    cout << "Ano: " << ano << endl << "Mes: " << mes << endl << "Marca: " << marca << endl << "Tipo: " << tipo;
    return 4;
}

float Motorizado::calcImposto() const
{
    if(combustivel=="gasolina")
    {
        if(cilindrada<=1000)
        {
            if(ano>1995)
                return 14.56;
            else
                return 8.10;
        }
        if(cilindrada>1000 && cilindrada <= 1300)
        {
            if(ano>1995)
                return 29.06;
            else
                return 14.56;
        }
        if(cilindrada>1300 && cilindrada <= 1750)
        {
            if(ano>1995)
                return 45.15;
            else
                return 22.65;
        }
        if(cilindrada>1750 && cilindrada <= 2600)
        {
            if(ano>1995)
                return 113.98;
            else
                return 54.89;
        }
        if(cilindrada>2600 && cilindrada <= 3500)
        {
            if(ano>1995)
                return 181.17;
            else
                return 87.13;
        }
        if(cilindrada>3500)
        {
            if(ano>1995)
                return 320.89;
            else
                return 148.37;
        }
    }
    else
    {
        if(cilindrada<=1500)
        {
            if(ano>1995)
                return 14.56;
            else
                return 8.10;
        }
        if(cilindrada>1500 && cilindrada <= 2000)
        {
            if(ano>1995)
                return 29.06;
            else
                return 14.56;
        }
        if(cilindrada>2000 && cilindrada <= 3000)
        {
            if(ano>1995)
                return 45.15;
            else
                return 22.65;
        }
        else
        {
            if(ano>1995)
                return 113.98;
            else
                return 54.89;
        }

    }
}

float Bicicleta::calcImposto() const
{
    return 0;
}