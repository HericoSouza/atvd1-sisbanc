#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Cliente {
private:
    string nome;
    string cpf;

public:
    Cliente(string n, string c) {
        nome = n;
        cpf = c;
    }

    string getNome() {
        return nome;
    }

    string getCpf() {
        return cpf;
    }
};

class ContaBancaria {
private:
    int numero;
    double saldo;
    Cliente titular;

public:
    ContaBancaria(int num, Cliente t, double s = 0.0)
        : numero(num), titular(t), saldo(s) {}

    //Função de depositar
    void depositar(double valor) {
        if (valor > 0) {
            saldo += valor;
            cout << "Depositado com sucesso: R$ " << valor
                 << " na conta de numero " << numero << endl;
        } else {
            cout << "Valor invalido!" << endl;
        }
    }

    //Função de sacar
    void sacar(double valor) {
        if (valor > 0 && valor <= saldo) {
            saldo -= valor;
            cout << "Sacado com sucesso: R$ " << valor
                 << " na conta de numero " << numero << endl;
        } else {
            cout << "Saldo insuficiente ou valor invalido!" << endl;
        }
    }

    // Transferência para uma conta
    void transferir(double valor, ContaBancaria &destino) {
        if (valor <= 0.0) {
            cout << "Valor invalido para transferencia!" << endl;
            return;
        }
        if (&destino == this) {
            cout << "Transferencia para a mesma conta nao e permitida." << endl;
            return;
        }
        if (valor > saldo) {
            cout << "Saldo insuficiente para transferencia!" << endl;
            return;
        }
        saldo -= valor;
        destino.saldo += valor;
        cout << fixed << setprecision(2);
        cout << "Transferido: R$ " << valor
             << " da conta " << numero
             << " para a conta " << destino.numero << endl;
    }

    // Transferência dividida entre duas contas
    void transferir(double valor, ContaBancaria &destino1, ContaBancaria &destino2) {
        if (valor <= 0.0) {
            cout << "Valor invalido para transferencia!" << endl;
            return;
        }
        if (&destino1 == this || &destino2 == this) {
            cout << "Transferencia para a mesma conta nao e permitida." << endl;
            return;
        }
        if (valor > saldo) {
            cout << "Saldo insuficiente para transferencia!" << endl;
            return;
        }
        saldo -= valor;
        destino1.saldo += valor / 2;
        destino2.saldo += valor / 2;
        cout << fixed << setprecision(2);
        cout << "Transferido: R$ " << valor/2
             << " para cada conta (" << destino1.numero
             << " e " << destino2.numero
             << ") da conta " << numero << endl;
    }

    //Função que mostra o saldo
    void exibirSaldo() {
        cout << fixed << setprecision(2);
        cout << "Saldo atual da conta " << numero << ": R$ " << saldo << endl;
    }
    
    //Função que mostra infos do cliente e da sua conta
    void exibirInformacoes() {
        cout << "Titular: " << titular.getNome() 
             << ", CPF: " << titular.getCpf() << endl;
        cout << "Número da Conta: " << numero 
             << ", Saldo: R$ " << fixed << setprecision(2) << saldo << endl;
    }
};

int main() {
    // Criação dos clientes
    Cliente cliente1("Ana", "111.111.111-11");
    Cliente cliente2("Bruno", "222.222.222-22");
    Cliente cliente3("Carla", "333.333.333-33");

    // Criação das contas bancárias com saldos iniciais
    ContaBancaria conta1(1001, cliente1, 1000.0);
    ContaBancaria conta2(1002, cliente2);
    ContaBancaria conta3(1003, cliente3);

    // Exibe o saldo inicial da conta de Ana
    conta1.exibirSaldo();

    // Ana transfere R$200 para Bruno
    conta1.transferir(200.0, conta2);

    // Ana transfere R$300 divididos entre Bruno e Carla
    conta1.transferir(300.0, conta2, conta3);

    // Exibição dos saldos finais
    cout << endl;
    conta1.exibirInformacoes();
    conta2.exibirInformacoes();
    conta3.exibirInformacoes();

    return 0;
}
