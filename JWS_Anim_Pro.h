/* * ==============================================================================
 * LIBRARY   : JWS_Anim_Pro.h (Animasi LED Matrix Pro untuk JWS)
 * AUTHOR    : Ahmad AlBrabasi & Practical Developer JWS
 * VERSI     : 1.0.0 (Maret 2026)
 * ==============================================================================
 * DESKRIPSI:
 * Library ini dirancang khusus untuk proyek Jam Waktu Sholat (JWS) menggunakan
 * panel LED RGB HUB75 (ESP32-HUB75-I2S-DMA). Menghadirkan transisi visual yang 
 * halus, elegan, dan profesional setara software Huidu.
 * * FITUR UNGGULAN:
 * 1. Non-Blocking: Semua animasi menggunakan millis(), tidak mengganggu RTC/Adzan.
 * 2. Multi-Area: Bisa menentukan koordinat x, y, w, h untuk setiap animasi.
 * 3. Step-by-Step Scroll: Animasi naik-berhenti-naik (Cocok untuk Saldo Masjid).
 * 4. Auto-Rainbow: Efek warna pelangi MeJiKuHiBiNiU yang sinkron secara global.
 * 5. Universal Logic: Mendukung berbagai ukuran panel (64x32, 128x32, dst).
 * * CARA PENGGUNAAN:
 * 1. Sertakan library: #include <JWS_Anim_Pro.h>
 * 2. Buat objek: JWS_Anim_Pro anim(*dma_display);
 * 3. Panggil di loop: anim.swimBoxAnim(0, 0, 64, 16, 25, "TEKS INFO");
 * * DATA OUTPUT / VARIABEL PUBLIK:
 * - anim.warnaGlobal : Menghasilkan warna pelangi yang berubah otomatis.
 * ==============================================================================
 */

#ifndef JWS_ANIM_PRO_H
#define JWS_ANIM_PRO_H

#include <Arduino.h>
#include <ESP32-HUB75-I2S-DMA-2.0.0.h>

class JWS_Anim_Pro {
  public:
    // Konstruktor: Menerima pointer ke objek dma_display
    JWS_Anim_Pro(MatrixPanel_I2S_DMA &display);

    // --- FUNGSI UTAMA ---
    
    // dimWarnaAnim: Mengelola perubahan warna pelangi secara otomatis
    // Param: interval (ms) untuk kecepatan pergantian warna
    void dimWarnaAnim(int interval);

    // runTextAnim: Menampilkan teks berjalan secara horizontal
    // Param: y (baris), speed (kecepatan), teks, warna
    void runTextAnim(int y, int speed, const char* teks, uint16_t warna);

    // swimBoxAnim: Efek pintu kupu-kupu (membuka/menutup dari tengah)
    // Param: x, y, w, h, speed, teks
    void swimBoxAnim(int x, int y, int w, int h, int speed, const char* teks);

    // scrollUpStep: Animasi vertikal berjenjang (Naik -> Diam -> Naik)
    // Param: x, y, w, h, speed, array data teks, jumlah data
    void scrollUpStep(int x, int y, int w, int h, int speed, const char* data[], int totalData);

    // Variabel warna yang bisa digunakan oleh fungsi lain di luar library
    uint16_t warnaGlobal;

  private:
    MatrixPanel_I2S_DMA* _display;
    
    // Internal Timers & State Management
    unsigned long _lastDim, _lastRun, _lastSwim, _lastScroll, _timerWait;
    int _colorIdx, _runPosX, _swimProgress, _swimStep, _scrollStep, _dataIdx, _currentY;
    
    // Konstanta Warna MeJiKuHiBiNiU
    const uint16_t _pelangi[7] = {
        0xF800, 0xFD20, 0xFFE0, 0x07E0, 0x001F, 0x4810, 0xA81F
    };
};

#endif
