[README.en.md](README.en.md)

因[原版ArduinoSTL](https://github.com/mike-matera/ArduinoSTL)作者長期不更新（202203~202212），本人將此分支發佈到Arduino公開庫，改名為Cpp_Standard_Library以示區分。

本函式庫試圖在Arduino上實作C++11~17標準函式庫（STL）的大部分功能。除了ArduinoSTL以外，本函式庫部分功能實作也參考了MSVC、LLVM、boost和GCC。因為是依照STL做的接口，所以不需要另外寫文檔，你可以參考任何一個權威的STL文檔。除非另有說明，否則本函式庫的使用方法應該是一樣的，如果不一樣那應該就是個bug，歡迎提交Issue。

如果你需要某些標準函式庫中應有而本函式庫中尚未提供的功能，也歡迎提交Issue，作者將會優先為你實作。

支援以下架構，但需要額外配置：

-   AVR，要求C++17。需要更改`%LOCALAPPDATA%\Arduino15\packages\arduino\hardware\avr\*.*.*\platform.txt`中的`-std=gnu++11`為`-std=gnu++17`
-   SAM，要求C++11。需要在`%LOCALAPPDATA%\Arduino15\packages\arduino\hardware\sam\*.*.*\platform.txt`中的`compiler.cpp.flags`中添加`-fpermissive`旗幟
-   ESP32，要求C++17。需要更改`%LOCALAPPDATA%\Arduino15\packages\arduino\hardware\esp32\*.*.*\platform.txt`中的所有`-std=gnu++11`為`-std=gnu++17`，並在`compiler.cpp.flags`中添加`-fpermissive`旗幟

在包含任何C++標準頭檔之前，必須先包含`Cpp_Standard_Library.h`。這是對 Arduino IDE 的提示，告訴編譯器必須將本函式庫納入編譯流程。

# 招牌功能（不限於此）

-   `<algorithm> fill_n shuffle`
-   `<chrono> chrono::duration`
-   `<dynarray>`曾經有望進入C++標準的廢案。雖然最終沒能進入，但作為`array`和`vector`的中間類型非常有用。
-   `<functional> std::function`非標準行為：呼叫空物件時不做任何事。這是因為標準行為是應當拋出異常，但Arduino不支援異常。如果希望呼叫空物件時不做任何事，則可無需判斷物件是否為空而直接呼叫。
-   `<iostream> cin cout endl`使用`Serial`實現標準輸入輸出流。但是，使用前仍必須手動`Serial.begin`。不應在`setup`函數之前的全域變數初始化階段使用`Serial`，因為在`setup`被呼叫之前無法保證`Serial`已完成初始化，此時使用`Serial`是未定義行為。另外測試發現，對於SAM架構，串列埠剛完成初始化後可能會傳送一些隨機字節，這似乎是硬體設計缺陷使然，軟體層面無法解決，接收端必須考慮到這個問題。
-   `<map>`
-   `<memory> unique_ptr make_unique`
-   `<random>`，`mt19937`佔記憶體較多（約5K），謹慎使用。`ArduinoUrng`是Arduino平台特定的`UniformRandomNumberGenerator`，可用於`shuffle`，屬於軟體偽隨機產生器，需設定隨機種子。 ESP32架構還額外支持`EspUrng`，是硬體真隨機產生器，不支援設定種子。
-   `<ratio>`
-   `<set>`
-   `<type_traits>`
-   `<vector>`
-   `std::begin std::end`
-   如果編譯器隨附了某些重名的標準函式庫功能，將優先使用隨附的版本。編譯器可能也隨附了本函式庫未提供的其它標準函式庫功能，那些功能也不會與本函式庫衝突。

安裝後記得查看範例項目！

# 原版README（僅供參考，部分內容已過時）

這是封裝為 Arduino 函式庫的 C++ 標準函式庫的實作。該庫透過將關鍵的 C++ 功能添加到 Arduino 環境中來支援我的 CS-11M 課程的教學。

該函式庫是從 uClibc++ 移植的：

<http://git.uclibc.org/uClibc++>

使用 Andy Brown 的 Arduino 庫的串流實現：

<http://andybrown.me.uk/2011/01/15/the-standard-template-library-stl-for-avr-with-c-streams/>

## 使用 printf() 和 scanf()

ArduinoSTL 頭檔包含將您選擇的序列埠綁定到的程式碼
stdio 原語。這會自動發生，但用戶仍然必須調用
串行.begin()

```c++
#include <ArduinoSTL.h>

void setup() {
  Serial.begin(9600); 
  printf("Hello World\n");
}
```

## 使用`cin`一個`cout`

當您包含此頭檔時，您將自動獲得 cin 和 cout 基於`Serial`。請參閱下文以了解如何指定您自己的設備。這是一個使用範例草圖`cin`和`cout`.

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

## 更改串口

您可以變更串口`cin`,`cout`和`printf()`使用。您可以使用內建序列埠（例如`Serial1`在 Leonardo 上）或者您可以使用軟體序列埠來實現`Stream`.

### 使用內建連接埠

在`src/ArduinoSTL.cpp`改變的值`ARDUINOSTL_DEFAULT_SERIAL`。保留其他預設值不註釋。

### 使用軟體序列埠。

放`ARDUINO_DEFAULT_SERAL`到`NULL`。註解掉其他預設值。

以下是使用 SofwareSerial 的範例草圖：

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

## 避免實例化`cin`和`cout`

註解掉`ARDUINOSTL_DEFAULT_CIN_COUT`並且什麼都不會被實例化。如果您打算選擇非預設串列端口，則必須註解掉該標誌。使用時沒有明顯的開銷`printf()`所以你目前無法避免初始化它。

## 已知的問題

使用列印浮點數和雙精度數`cout`忽略格式說明符。

uClibc 似乎相當完整。即使 Arduino 可用的堆數量有限，字串和向量都可以工作。 uClibc++ 狀態頁面可以在這裡找到：

<https://cxx.uclibc.org/status.html>

始終使用最新的 Arduino IDE。本函式庫使用 Arduino IDE 函式庫規格 rev.2.1，其功能僅在 Arduino 1.6.10 及更高版本上可用。該規範可以在這裡找到：

<https://github.com/arduino/Arduino/wiki/Arduino-IDE-1.5:-Library-specification>

## 執照

uClibc++ 函式庫根據 LGPL 取得許可。該專案採用 LGPL 與其使用的大部分程式碼相容。除非另有說明，否則所有程式碼均根據 LGPL 獲得許可。有一個例外：

-   根據 Andy Brown 的意願，src/serstream 在 BSD 許可證下獲得許可：<http://andybrown.me.uk/terms-and-conditions/>
