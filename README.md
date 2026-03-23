# JWS_Anim_Pro
**Library Animasi LED Matrix HUB75 ESP32 untuk Jam Waktu Sholat (JWS) Indonesia.**

JWS_Anim_Pro adalah library yang dirancang khusus untuk mempermudah pembuat JWS di Indonesia dalam menciptakan tampilan yang dinamis, elegan, dan profesional. Library ini menggunakan logika *non-blocking* (`millis()`), sehingga tidak mengganggu akurasi waktu sholat dan jadwal adzan.

##  Fitur Utama
- **swimBoxAnim**: Efek pintu kupu-kupu (membuka/menutup dari tengah).
- **scrollUpStep**: Efek geser ke atas bertahap dengan jeda baca (Sangat cocok untuk Saldo/Laporan Keuangan Masjid).
- **runTextAnim**: Running text horizontal yang halus dengan fitur auto-reset.
- **dimWarnaAnim**: Otomatisasi perubahan warna teks (MeJiKuHiBiNiU) setiap interval tertentu.
- **Memory Efficient**: Menggunakan `PROGMEM` dan pointer untuk menghemat RAM ESP32.

##  Cara Instalasi
1. Download repository ini sebagai file ZIP.
2. Di Arduino IDE, pergi ke menu **Sketch** -> **Include Library** -> **Add .ZIP Library...**
3. Pilih file yang baru saja didownload.
4. Library siap digunakan!

## Contoh Penggunaan Sederhana
```cpp
#include <JWS_Anim_Pro.h>

// Inisialisasi
JWS_Anim_Pro anim(*dma_display);

void loop() {
  // Update warna pelangi tiap 500ms
  anim.dimWarnaAnim(500);

  // Animasi Pintu di baris atas
  anim.swimBoxAnim(0, 0, 64, 16, 25, "MASJID AL-IKHLAS");

  // Running Text dengan warna global
  anim.runTextAnim(22, 40, "Mari Rapatkan Shaf...", anim.warnaGlobal);
}
