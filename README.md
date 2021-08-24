このライブラリはGNU General Public Licenseで保護されています。

# SwitchDenGoMascon
このライブラリはArduino Unoで瑞起の電車でＧＯ！！専用ワンハンドルコントローラーを読み取るためのライブラリです。

# 必要なもの
このライブラリを使うにはUSBホストシールドとUSB Host Library Rev. 2.0が必要です。  
USB Host LibraryはArduinoのライブラリマネージャーか以下から入手できます。  
https://github.com/felis/USB_Host_Shield_2.0

# 使い方
USB関連の基本的な使い方はUSB Host Libraryの使用方法を参考にしてください。
またサンプルプログラムも参考にしてください。

## ライブラリのインクルード
「SwitchDenGoMascon.h」をインクルードしてください。  
USBハブを使用する場合は「usbhub.h」もインクルードしてください。  
USB Host Libraryでは「SPI.h」もインクルードするよう書かれていますが、無くても使えました。もしコンパイルエラーが起きたらインクルードしてみてください。

```
#include <SwitchDenGoMascon.h>
#include <usbhub.h>
#include <SPI.h>
```

## インスタンスの生成
USBクラスとSwitchDenGoMasconクラスのインスタンスを生成します。  
USBハブを使用する場合はUSBHubクラスも生成してください。

```
USB Usb;
USBHub Hub(&Usb);
SwitchDenGoMascon SwitchDenGo(&Usb);
```

## USBクラスの初期化と実行
setup内で「Init()」を実行して初期化してください。loop内で「Task()」を実行してください。  


```
void setup() {
  Usb.Init();
}

void loop(){
  Usb.Task();
}
```

## メソッド
SwitchDenGoMasconクラスのインスタンスを生成すると以下のメソッドが使用できます。

### connected()
マスコンを接続しているかどうかをboolで返します

```
SwitchDenGo.connected();  //マスコンを接続していればtrueが返る
```

### getMascon()
マスコンの位置を取得できます。  
引数を未指定にするとマスコン位置を0から14の数値で返します。0がEB、9がN、14がP5です。  
引数にPowerLevelを指定すると力行レベルを0から5で、BrakeLevelを指定すると制動レベルを0から9で取得できます。  


```
SwitchDenGo.geMascon();  //マスコン位置が0から14で返る
SwitchDenGo.geMascon(PowerLevel);  //力行レベルが0から5で返る
SwitchDenGo.geMascon(BrakeLevel);  //制動レベルが0から9で返る　９はEB
```

### isPressed()
引数で指定したコントローラーのボタンが押されているかを取得できます。


```
SwitchDenGo.isPressed(BtnA);  //Aボタンが押されていればtrueが返る
SwitchDenGo.isPressed(HatUp);  //上ボタンが押されていればtrueが返る
```    
  
引数に使えるボタン定義は以下の通りです。

```
BtnL //Lボタン
BtnR //Rボタン
BtnZl //ZLボタン
BtnZr //ZRボタン
BtnB //Bボタン
BtnA //Aボタン
BtnX //Xボタン
BtnY //Yボタン
BtnCapture //Captureボタン
BtnHome //Homeボタン
BtnPlus //プラスボタン
BtnMinus //マイナスボタン
HatUp //上ボタン
HatRight //右ボタン
HatDown //下ボタン
HatLeft //左ボタン
```
