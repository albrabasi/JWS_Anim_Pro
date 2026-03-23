#include <JWS_Anim_Pro.h>

// Konfigurasi Pin ESP32 untuk HUB75 (Sesuaikan dengan wiring masing-masing)
#define R1_PIN 25
#define G1_PIN 26
#define B1_PIN 27
#define R2_PIN 14
#define G2_PIN 12
#define B2_PIN 13
#define CH_A 23
#define CH_B 19
#define CH_C 5
#define CH_D 17
#define CH_E -1 // P5 32x64 biasanya tidak pakai E-Line
#define CLK 16
#define LAT 4
#define OE 15

MatrixPanel_I2S_DMA *dma_display = nullptr;
JWS_Anim_Pro *anim = nullptr;

// Data untuk Laporan Keuangan (Contoh)
const char* laporanKeuangan[] = {
  "SALDO JUMAT 1: 1.500K",
  "SALDO JUMAT 2: 2.100K",
  "SALDO JUMAT 3: 1.850K",
  "SALDO JUMAT 4: 3.200K"
};

void setup() {
  // Setup Panel DMA
  HUB75_I2S_CFG mxConfig(64, 32, 1); // Lebar 64, Tinggi 32, 1 Panel
  dma_display = new MatrixPanel_I2S_DMA(mxConfig);
  dma_display->begin();
  dma_display->setBrightness8(90);
  dma_display->clearScreen();

  // Inisialisasi Library Animasi Kita
  anim = new JWS_Anim_Pro(*dma_display);
}

void loop() {
  // 1. Update warna pelangi setiap 500ms
  anim->dimWarnaAnim(500);

  // 2. Tampilkan Info Masjid dengan Animasi Pintu (Atas: y=0, h=16)
  anim->swimBoxAnim(0, 0, 64, 16, 25, "MASJID RAYA");

  // 3. Tampilkan Laporan Keuangan dengan Scroll Up Step (Bawah: y=18, h=14)
  // Data diambil dari array laporanKeuangan (4 data)
  anim->scrollUpStep(0, 18, 64, 14, 30, laporanKeuangan, 4);

  // 4. Running Text di baris paling bawah (Jika area cukup)
  // anim->runTextAnim(24, 40, "Selamat Beribadah...", anim->warnaGlobal);
}
