#ifndef JWS_ANIM_PRO_H
#define JWS_ANIM_PRO_H

#include <Arduino.h>
#include <ESP32-HUB75-I2S-DMA-2.0.0.h>

class JWS_Anim_Pro {
  public:
    // Konstruktor
    JWS_Anim_Pro(MatrixPanel_I2S_DMA &display);

    // Fungsi Utama (Warna & Running Text)
    void dimWarnaAnim(int interval);
    void runTextAnim(int y, int speed, const char* teks, uint16_t warna);

    // Fungsi Animasi Box/Pintu
    void swimBoxAnim(int x, int y, int w, int h, int speed, const char* teks);

    // Fungsi Animasi Vertikal (Laporan Keuangan/Saldo)
    void scrollUpStep(int x, int y, int w, int h, int speed, const char* data[], int totalData);

    // Variabel Publik agar bisa diakses di Sketch Utama
    uint16_t warnaGlobal;

  private:
    MatrixPanel_I2S_DMA* _display;
    
    // Timer & Status Management
    unsigned long _lastDim, _lastRun, _lastSwim, _lastScroll, _timerWait;
    int _colorIdx, _runPosX, _swimProgress, _swimStep, _scrollStep, _dataIdx, _currentY;
    
    // Array Warna MeJiKuHiBiNiU (Internal)
    const uint16_t _pelangi[7] = {
        0xF800, 0xFD20, 0xFFE0, 0x07E0, 0x001F, 0x4810, 0xA81F
    };
};

#endif
