// ---- Classe LED ---- //
class Led {
  private:
    int pin; // Guarda o pino do LED

  public:
    // Construtor da classe
    Led(int p) {
      pin = p;           // Corrigido (antes estava invertido)
      pinMode(pin, OUTPUT);
    }

    void on() {
      digitalWrite(pin, HIGH);
    }

    void off() {
      digitalWrite(pin, LOW);
    }
};


// ---- Classe Botao ---- //
// IMPORTANTE: sem acentos no nome!
class Botao {
  private:
    int pin;

  public:
    Botao(int p) {
      pin = p;
      pinMode(pin, INPUT_PULLUP); // Botao com resistor interno
    }

    bool pressionado() {
      return digitalRead(pin) == LOW; // LOW = apertado
    }
};


// ---- Classe Semaforo ---- //
class Semaforo {
  private:
    Led* verde;
    Led* amarelo;
    Led* vermelho;
    int estado; // 0 = verde, 1 = amarelo, 2 = vermelho

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
      estado = 0; // começa no verde
    }

    void proximo() {
      apagarTodos(); // garante que só 1 LED ficará ligado

      if (estado == 0) {
        verde->on();
        estado = 1;
      } 
      else if (estado == 1) {
        amarelo->on();
        estado = 2;
      } 
      else if (estado == 2) {
        vermelho->on();
        estado = 0;
      }
    }
};


// ---- Instanciando os objetos ---- //

// LEDs nos pinos digitais
Led verde(10);
Led amarelo(9);
Led vermelho(8);

// Botao no pino 2
Botao botao(2);

// Semaforo recebendo os 3 LEDs
Semaforo semaforo(&verde, &amarelo, &vermelho);


void setup() {
  Serial.begin(9600);
  semaforo.proximo(); // Inicia com a cor verde ligada
}

void loop() {
  if (botao.pressionado()) {
    semaforo.proximo(); 
    delay(2000); // Debounce simples para evitar multiplos cliques
  }
}
