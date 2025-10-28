// ---- Classe LED ---- //
class Led {
  private:
    int pin;

  public:
    Led(int p) {
      pin = p;
      pinMode(pin, OUTPUT);
    }

    void on() {
      digitalWrite(pin, HIGH);
    }

    void off() {
      digitalWrite(pin, LOW);
    }
};

// ---- Classe Semaforo ---- //
class Semaforo {
  private:
    Led* verde;
    Led* amarelo;
    Led* vermelho;

    int estado; // 0 = verde, 1 = amarelo, 2 = vermelho
    unsigned long tempoAnterior;
    unsigned long duracao;

    void apagarTodos() {
      verde->off();
      amarelo->off();
      vermelho->off();
    }

  public:
    Semaforo(Led* v, Led* a, Led* r) {
      verde = v;
      amarelo = a;
      vermelho = r;
      estado = 0;
      tempoAnterior = 0;
      duracao = 0;
    }

    // Inicia no verde
    void iniciar() {
      apagarTodos();
      estado = 0;
      verde->on();
      tempoAnterior = millis();
      duracao = 6000UL; // 6 segundos (verde)
    }

    // Atualiza automaticamente de acordo com o tempo
    void atualizar() {
      unsigned long agora = millis();
      if (agora - tempoAnterior >= duracao) {
        proximo();
        tempoAnterior = agora;
      }
    }

  private:
    void proximo() {
      apagarTodos();

      if (estado == 0) {
        amarelo->on();
        estado = 1;
        duracao = 2000UL; // 2 segundos (amarelo)
      } 
      else if (estado == 1) {
        vermelho->on();
        estado = 2;
        duracao = 4000UL; // 4 segundos (vermelho)
      } 
      else {
        verde->on();
        estado = 0;
        duracao = 6000UL; // 6 segundos (verde)
      }
    }
};

// ---- Instanciando os objetos ---- //
Led verde(10);
Led amarelo(9);
Led vermelho(8);

Semaforo semaforo(&verde, &amarelo, &vermelho);

void setup() {
  Serial.begin(9600);
  semaforo.iniciar();
}

void loop() {
  semaforo.atualizar(); // troca automaticamente
}
