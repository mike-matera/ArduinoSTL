parce que[ArduinoSTL d'origine](https://github.com/mike-matera/ArduinoSTL)作者长期不更新（202203~202212），本人将此分支发布到Arduino公开库，改名为Cpp_Standard_Library以示区分。

Cette bibliothèque tente d'implémenter la plupart des fonctions de la bibliothèque standard C++ 11~17 (STL) sur Arduino. En plus d'ArduinoSTL, certaines fonctions de cette bibliothèque font également référence à MSVC, LLVM et boost. L'interface étant basée sur STL, il n'est pas nécessaire d'écrire des documents supplémentaires. Vous pouvez vous référer à n'importe quel document STL faisant autorité. Sauf indication contraire, l'utilisation de cette bibliothèque doit être la même. Si elle est différente, cela devrait être un bug. Vous êtes invités à soumettre un problème.

Si vous avez besoin de certaines fonctions qui se trouvent dans la bibliothèque standard mais qui ne sont pas fournies dans cette bibliothèque, vous pouvez également soumettre un problème, et l'auteur le mettra en œuvre pour vous en premier.

Prend actuellement en charge les architectures AVR et SAM. Il n'est pas prévu de prendre en charge ESP32 pour le moment, car ESP32 a officiellement fourni une bibliothèque standard, et l'utilisation simultanée de deux ensembles de bibliothèques standard entraînera de nombreux problèmes difficiles à résoudre.

Depuis le[ArduinoSTL d'origine](https://github.com/mike-matera/ArduinoSTL)n'a pas de mises à jour ou depuis longtemps (202203~202212), j'ai publié cette branche dans la bibliothèque publique Arduino et je l'ai renommée Cpp_Standard_Library pour la distinguer.

Cette bibliothèque tente d'implémenter la plupart des fonctionnalités de la bibliothèque standard C++ 11~17 (STL) sur Arduino. En plus d'ArduinoSTL, certaines des implémentations fonctionnelles de cette bibliothèque font également référence à MSVC, LLVM et boost. Étant donné que les interfaces sont réalisées selon STL, il n'est pas nécessaire d'écrire une documentation supplémentaire, vous pouvez vous référer à n'importe quel document STL faisant autorité. Sauf indication contraire, l'utilisation et le comportement de cette bibliothèque doivent être les mêmes ; si différent, il devrait s'agir d'un bug et n'hésitez pas à soumettre un problème.

Si vous avez besoin de certaines fonctionnalités disponibles dans la bibliothèque standard mais qui ne le sont pas encore dans cette bibliothèque, vous êtes également invités à soumettre un numéro, et l'auteur se donnera la priorité de l'implémenter pour vous.

Les architectures AVR et SAM sont actuellement prises en charge. Il n'est actuellement pas prévu de prendre en charge ESP32, car ESP32 a officiellement fourni une bibliothèque standard. L’utilisation de deux bibliothèques standards en parallèle génère de nombreux problèmes délicats.

# Fonctionnalités de signature (sans s'y limiter) Fonctionnalités de signature (sans s'y limiter)

-   `<algorithm> fill_n shuffle`
-   `<chrono> chrono::duration`
-   `<iostream> cin cout`Utiliser le port série comme flux d'entrée et de sortie standard
-   `<map>`
-   `<memory> unique_ptr`
-   `<random> mt19937, ArduinoUrng`：`mt19937`Il prend beaucoup de mémoire (environ 5K), alors utilisez-le avec prudence.`ArduinoUrng`est-ce spécifique à la plateforme Arduino`UniformRandomNumberGenerator`,Peut être utilisé comme`shuffle`。
-   `<ratio>`
-   `<set>`
-   `<type_traits>`
-   `<vector>`
-   `<xutility> std::begin std::end`

# README original (à titre de référence uniquement, certains contenus sont obsolètes)

Il s'agit d'une implémentation d'une bibliothèque standard C++ présentée sous forme de bibliothèque Arduino. La bibliothèque prend en charge l'enseignement de ma classe CS-11M en ajoutant des fonctionnalités clés C++ dans l'environnement Arduino.

La bibliothèque est portée depuis uClibc++ :

<http://git.uclibc.org/uClibc++>

Avec une implémentation de flux de la bibliothèque Arduino d'Andy Brown :

<http://andybrown.me.uk/2011/01/15/the-standard-template-library-stl-for-avr-with-c-streams/>

## Utilisation de printf() et scanf()

Le fichier d'en-tête ArduinoSTL contient du code pour lier un port série de votre choix à
les primitives stdio. Cela se produit automatiquement mais l'utilisateur doit quand même appeler
Série.begin()

```c++
#include <ArduinoSTL.h>

void setup() {
  Serial.begin(9600); 
  printf("Hello World\n");
}
```

## En utilisant`cin`un`cout`

Lorsque vous incluez ce fichier d'en-tête, vous obtenez automatiquement cin et cout en fonction de`Serial`. Voir ci-dessous pour savoir comment spécifier votre propre appareil. Voici un exemple de croquis utilisant`cin`et`cout`.

```c++
#include <ArduinoSTL.h>

using namespace std;

void setup() {
  Serial.begin(9600);
  cout << "Feed me an integers." << endl;
}

void loop() {
  int foo;
  if (cin >> foo) { 
    cout << "You fed me " << foo << endl;
  }else{
    cin.clear();
    cin.ignore();
  }
}
```

## Changer le port série

Vous pouvez changer le port série utilisé`cin`,`cout`et`printf()`utiliser. Vous pouvez utiliser des ports série intégrés (par ex.`Serial1`sur Leonardo) ou vous pouvez utiliser des ports série logiciels qui implémentent`Stream`.

### Utilisation d'un port intégré

Dans`src/ArduinoSTL.cpp`changer la valeur de`ARDUINOSTL_DEFAULT_SERIAL`. Laissez les autres valeurs par défaut sans commentaire.

### Utilisation d'un port SoftwareSerial.

Ensemble`ARDUINO_DEFAULT_SERAL`à`NULL`. Commentez les autres valeurs par défaut.

Voici un exemple de croquis qui utilise SoftwareSerial :

```c++
#include <ArduinoSTL.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(0, 1);

namespace std { 
  ohserialstream cout(mySerial);
  ihserialstream cin(mySerial);
}

void setup() {
  mySerial.begin(9600);
  ArduinoSTL_Serial.connect(mySerial);
}
```

## Éviter l'instanciation de`cin`et`cout`

Comment out`ARDUINOSTL_DEFAULT_CIN_COUT`et rien ne sera instancié. Vous devez commenter cet indicateur si vous avez l'intention de sélectionner un port série autre que celui par défaut. Il n'y a pas de frais généraux appréciables pour l'utilisation`printf()`vous ne pouvez donc pas actuellement éviter de l'initialiser.

## Problèmes connus

Impression de flotteurs et de doubles en utilisant`cout`ignore les spécificateurs de format.

uClibc seems to be fairly complete. Strings and vectors both work, even with the limited amount of heap available to Arduino. The uClibc++ status page can be found here: 

<https://cxx.uclibc.org/status.html>

Utilisez toujours le dernier IDE Arduino. Cette bibliothèque utilise la spécification de la bibliothèque Arduino IDE rev.2.1 avec des fonctionnalités disponibles uniquement sur Arduino 1.6.10 et versions ultérieures. Le cahier des charges peut être trouvé ici :

<https://github.com/arduino/Arduino/wiki/Arduino-IDE-1.5:-Library-specification>

## Licence

La bibliothèque uClibc++ est sous licence LGPL. Ce projet adopte la LGPL pour être compatible avec la majeure partie du code qu'il utilise. Sauf indication contraire, tout le code est sous licence LGPL. Il y a une exception :

-   src/serstream est sous licence BSD selon les souhaits d'Andy Brown ici :<http://andybrown.me.uk/terms-and-conditions/>
