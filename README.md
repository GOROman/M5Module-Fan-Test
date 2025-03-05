# M5Module-Fan-Test
M5Stack Fan Module v1.1 (STM32F030) テストプログラム

## 概要
このプロジェクトは、M5Stack Fan Module v1.1 (STM32F030)を制御・テストするためのPlatformIOプロジェクトです。M5Unifiedライブラリを使用して、FANモジュールの様々な機能を制御し、動作状態をリアルタイムで表示します。

## 機能
- ファンの動作状態（稼働/停止）の表示と制御
- PWM周波数の表示（1KHz/12KHz/24KHz/48KHz）
- PWMデューティサイクル（0-100%）の表示と調整
- 現在の回転数（RPM）のリアルタイム表示

## 操作方法
- ボタンA：ファンの稼働/停止を切り替え
- ボタンB：デューティサイクルを10%ずつ減少（0%になると100%に戻る）
- ボタンC：デューティサイクルを10%ずつ増加（100%になると0%に戻る）

## 必要なハードウェア
- M5Stack Core S3（または互換機）
- M5Stack Fan Module v1.1 (STM32F030)

## 必要なライブラリ
- [M5Unified](https://github.com/m5stack/M5Unified)
- [M5Module-Fan](https://github.com/m5stack/M5Module-Fan)

## 接続方法
M5Stack Fan ModuleをM5Stack Core S3（または互換機）のポートに接続します。このプログラムではWire1（I2C）を使用し、SCLはピン12、SDAはピン11に設定されています。

## 技術的な詳細
- I2Cアドレス：MODULE_FAN_BASE_ADDR（デフォルト）
- I2C速度：400kHz
- デフォルトPWM周波数：1KHz
- デフォルトデューティサイクル：80%

