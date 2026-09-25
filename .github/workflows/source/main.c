/* ============================================================
   DSi IA - Sistema de charla + calculadora + conocimientos
   ============================================================ */

int es_digito(char c) {
    return c >= '0' && c <= '9';
}

// Calculadora simple: soporta +, -, *, /, ^
int calcular_expresion(const char *expr, int *resultado) {
    char buffer[64];
    strncpy(buffer, expr, 63);
    buffer[63] = 0;
    a_minusculas(buffer);

    // Limpiar espacios y texto innecesario
    char limpio[64];
    int j = 0;
    for (int i = 0; buffer[i] && j < 63; i++) {
        if (buffer[i] != ' ') {
            limpio[j++] = buffer[i];
        }
    }
    limpio[j] = 0;

    // Buscar el operador
    char op = 0;
    int pos_op = -1;
    for (int i = 1; limpio[i]; i++) { // empezamos en 1 para permitir números negativos
        if (limpio[i] == '+' || limpio[i] == '-' || limpio[i] == '*' || 
            limpio[i] == 'x' || limpio[i] == '/' || limpio[i] == '^') {
            op = limpio[i];
            if (op == 'x') op = '*';
            pos_op = i;
            break;
        }
    }

    if (pos_op == -1) return 0; // no hay operador

    // Separar los dos números
    char izq[32] = {0};
    char der[32] = {0};
    strncpy(izq, limpio, pos_op);
    izq[pos_op] = 0;
    strcpy(der, limpio + pos_op + 1);

    int a = atoi(izq);
    int b = atoi(der);

    switch (op) {
        case '+': *resultado = a + b; break;
        case '-': *resultado = a - b; break;
        case '*': *resultado = a * b; break;
        case '/': 
            if (b == 0) return 0;
            *resultado = a / b; 
            break;
        case '^': {
            *resultado = 1;
            for (int i = 0; i < b; i++) *resultado *= a;
            break;
        }
        default: return 0;
    }
    return 1;
}

void responder_charla(const char *msg) {
    char m[MAX_INPUT];
    strncpy(m, msg, MAX_INPUT-1);
    m[MAX_INPUT-1] = 0;
    a_minusculas(m);

    iprintf("\n\nDSi IA: ");

    // ========== CALCULADORA ==========
    if (contiene(m, "cuanto es") || contiene(m, "cuánto es") || 
        contiene(m, "calcula") || contiene(m, "resuelve") ||
        (strchr(m, '+') || strchr(m, '-') || strchr(m, '*') || 
         strchr(m, 'x') || strchr(m, '/') || strchr(m, '^'))) {
        
        int res = 0;
        if (calcular_expresion(m, &res)) {
            iprintf("El resultado es: %d", res);
            return;
        }
    }

    // ========== SALUDOS ==========
    if (contiene(m, "hola") || contiene(m, "buenos") || contiene(m, "buenas") || contiene(m, "hey")) {
        iprintf("Hola! Soy DSi IA, tu asistente escolar. Puedes preguntarme de Matematicas, Espanol, Quimica o pedirme que calcule algo. En que te ayudo?");
    }
    else if (contiene(m, "como estas") || contiene(m, "cómo estás") || contiene(m, "que tal")) {
        iprintf("Estoy muy bien, gracias. Lista para ayudarte con tus tareas y dudas. Y tu, como te va en la escuela?");
    }
    else if (contiene(m, "quien eres") || contiene(m, "quién eres") || contiene(m, "como te llamas")) {
        iprintf("Soy DSi IA, una inteligencia escolar hecha para tu DSi XL. Se de Matematicas, Espanol, Quimica y puedo resolver operaciones.");
    }
    else if (contiene(m, "que haces") || contiene(m, "qué haces")) {
        iprintf("Estoy aqui para ayudarte a estudiar y resolver dudas. Puedes preguntarme definiciones, pedirme que calcule algo o practicar con el modo examen.");
    }
    else if (contiene(m, "gracias")) {
        iprintf("De nada! Me alegra ayudarte. Sigue preguntando todo lo que necesites.");
    }
    else if (contiene(m, "adios") || contiene(m, "adiós") || contiene(m, "hasta luego") || contiene(m, "bye")) {
        iprintf("Hasta luego! Que te vaya muy bien en tus estudios. Vuelve cuando quieras.");
    }

    // ========== MATEMÁTICAS ==========
    else if (contiene(m, "que es una fraccion") || contiene(m, "qué es una fracción") || contiene(m, "que son las fracciones")) {
        iprintf("Una fraccion representa partes de un todo. Tiene numerador (arriba) y denominador (abajo). Ejemplo: 3/4 significa 3 partes de 4.");
    }
    else if (contiene(m, "que es una ecuacion") || contiene(m, "qué es una ecuación")) {
        iprintf("Una ecuacion es una igualdad que contiene una incognita (x). Resolverla significa encontrar el valor de x. Ejemplo: 2x + 4 = 10 → x = 3.");
    }
    else if (contiene(m, "como se resuelve una ecuacion") || contiene(m, "cómo se resuelve")) {
        iprintf("Para ecuaciones de primer grado: 1) Pasa los terminos con x a un lado y los numeros al otro. 2) Despeja x. 3) Verifica. Ejemplo: 3x - 5 = 10 → 3x = 15 → x = 5.");
    }
    else if (contiene(m, "que es una potencia") || contiene(m, "qué es una potencia")) {
        iprintf("Una potencia es multiplicar un numero por si mismo varias veces. Ejemplo: 2^4 = 2x2x2x2 = 16. La base es 2 y el exponente es 4.");
    }
    else if (contiene(m, "que es raiz cuadrada") || contiene(m, "qué es raíz cuadrada")) {
        iprintf("La raiz cuadrada de un numero es el valor que, multiplicado por si mismo, da ese numero. Ejemplo: raiz de 49 = 7 porque 7x7=49.");
    }
    else if (contiene(m, "que es el area") || contiene(m, "cómo se calcula el área")) {
        iprintf("El area mide la superficie. Cuadrado: lado x lado. Rectangulo: base x altura. Triangulo: (base x altura)/2. Circulo: pi x radio^2.");
    }
    else if (contiene(m, "que es el perimetro") || contiene(m, "qué es el perímetro")) {
        iprintf("El perimetro es la suma de todos los lados de una figura. Cuadrado: 4 x lado. Rectangulo: 2 x (largo + ancho).");
    }
    else if (contiene(m, "que es un porcentaje") || contiene(m, "qué es un porcentaje")) {
        iprintf("Un porcentaje es una fraccion de 100. Ejemplo: 25% de 80 = 0.25 x 80 = 20. Se usa mucho en descuentos y estadistica.");
    }

    // ========== ESPAÑOL ==========
    else if (contiene(m, "que es un verbo") || contiene(m, "qué es un verbo")) {
        iprintf("Un verbo expresa acciones, estados o procesos. Ejemplos: correr, estudiar, ser, estar, pensar. Es el nucleo del predicado.");
    }
    else if (contiene(m, "que es un sustantivo") || contiene(m, "qué es un sustantivo") || contiene(m, "que es un nombre")) {
        iprintf("Un sustantivo nombra personas, animales, cosas, lugares o ideas. Ejemplos: casa, Juan, perro, felicidad, escuela.");
    }
    else if (contiene(m, "que es un adjetivo") || contiene(m, "qué es un adjetivo")) {
        iprintf("Un adjetivo describe o califica al sustantivo. Nos dice como es algo. Ejemplos: grande, inteligente, rojo, rapido.");
    }
    else if (contiene(m, "que es un adverbio") || contiene(m, "qué es un adverbio")) {
        iprintf("Un adverbio modifica al verbo, adjetivo u otro adverbio. Indica como, cuando o donde. Ejemplos: rapidamente, muy, aqui, nunca, bien.");
    }
    else if (contiene(m, "que es el sujeto") || contiene(m, "qué es el sujeto")) {
        iprintf("El sujeto es quien realiza la accion o de quien se habla en la oracion. Ejemplo: 'Ana estudia' → Ana es el sujeto.");
    }
    else if (contiene(m, "que es el predicado") || contiene(m, "qué es el predicado")) {
        iprintf("El predicado es lo que se dice del sujeto y contiene al verbo. Ejemplo: 'Ana estudia matematicas' → 'estudia matematicas' es el predicado.");
    }
    else if (contiene(m, "que es una metafora") || contiene(m, "qué es una metáfora")) {
        iprintf("La metafora es una figura literaria que identifica una cosa con otra sin usar 'como'. Ejemplo: 'Sus ojos son dos luceros'.");
    }
    else if (contiene(m, "que es un diptongo") || contiene(m, "qué es un diptongo")) {
        iprintf("Diptongo: dos vocales juntas en la misma silaba. Ejemplo: tierra, cuadro, ciudad, cuidado.");
    }
    else if (contiene(m, "que es un hiato") || contiene(m, "qué es un hiato")) {
        iprintf("Hiato: dos vocales que se separan en silabas diferentes. Ejemplo: poeta (po-e-ta), raiz (ra-iz), aereo.");
    }
    else if (contiene(m, "que es sujeto tacito") || contiene(m, "qué es sujeto tácito")) {
        iprintf("El sujeto tacito no se escribe pero se entiende por el verbo. Ejemplo: 'Estudiamos juntos' (nosotros).");
    }

    // ========== QUÍMICA ==========
    else if (contiene(m, "que es la quimica") || contiene(m, "qué es la química") || contiene(m, "que es quimica")) {
        iprintf("La Quimica estudia la materia, su composicion, propiedades y las transformaciones que sufre. Analiza atomos, moleculas y reacciones.");
    }
    else if (contiene(m, "que es un atomo") || contiene(m, "qué es un átomo")) {
        iprintf("El atomo es la unidad mas pequena de un elemento. Tiene protones y neutrones en el nucleo, y electrones girando alrededor.");
    }
    else if (contiene(m, "que es una molecula") || contiene(m, "qué es una molécula")) {
        iprintf("Una molecula es la union de dos o mas atomos enlazados. Ejemplo: el agua (H2O) o el oxigeno (O2).");
    }
    else if (contiene(m, "que es el ph") || contiene(m, "qué es el ph")) {
        iprintf("El pH mide la acidez o basicidad. Va de 0 a 14. 7 es neutro, menor a 7 es acido y mayor a 7 es basico.");
    }
    else if (contiene(m, "que es un enlace ionico") || contiene(m, "qué es un enlace iónico")) {
        iprintf("Enlace ionico: un atomo cede electrones a otro (generalmente metal + no metal). Ejemplo: sal de mesa (NaCl).");
    }
    else if (contiene(m, "que es un enlace covalente") || contiene(m, "qué es un enlace covalente")) {
        iprintf("Enlace covalente: los atomos comparten electrones. Es comun entre no metales. Ejemplo: agua (H2O) y dioxido de carbono (CO2).");
    }
    else if (contiene(m, "que es un proton")) {
        iprintf("El proton es una particula con carga positiva que esta en el nucleo del atomo. Su numero define el elemento (numero atomico).");
    }
    else if (contiene(m, "que es un electron") || contiene(m, "qué es un electrón")) {
        iprintf("El electron es una particula con carga negativa que gira alrededor del nucleo del atomo. Es muy ligero.");
    }
    else if (contiene(m, "que es un neutron") || contiene(m, "qué es un neutrón")) {
        iprintf("El neutron no tiene carga (es neutro) y tambien esta en el nucleo junto con los protones.");
    }
    else if (contiene(m, "que es la tabla periodica") || contiene(m, "qué es la tabla periódica")) {
        iprintf("La tabla periodica organiza todos los elementos quimicos segun su numero atomico y propiedades. Fue creada por Mendeleiev.");
    }
    else if (contiene(m, "formula del agua") || contiene(m, "fórmula del agua")) {
        iprintf("La formula del agua es H2O: dos atomos de hidrogeno y uno de oxigeno.");
    }
    else if (contiene(m, "formula del dioxido") || contiene(m, "co2")) {
        iprintf("El dioxido de carbono tiene la formula CO2: un atomo de carbono y dos de oxigeno.");
    }

    // ========== RESPUESTA POR DEFECTO ==========
    else {
        iprintf("No estoy segura de entenderte completamente. Puedes preguntarme cosas como:\n");
        iprintf("- Que es la quimica?\n");
        iprintf("- Que es un verbo?\n");
        iprintf("- Cuanto es 56 + 7\n");
        iprintf("- Explicame las fracciones\n");
        iprintf("O usa el modo Leccion/Examen del menu.");
    }
}
