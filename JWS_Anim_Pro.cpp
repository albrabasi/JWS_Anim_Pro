#include "JWS_Anim_Pro.h"

// Konstruktor: Inisialisasi variabel awal
JWS_Anim_Pro::JWS_Anim_Pro(MatrixPanel_I2S_DMA &display) {
    _display = &display;
    _lastDim = _lastRun = _lastSwim = _lastScroll = 0;
    _colorIdx = _swimProgress = _swimStep = _scrollStep = _dataIdx = 0;
    _runPosX = display.width();
    _currentY = display.height();
    warnaGlobal = 0xFFFF; // Default Putih
}

// 1. Fungsi Ganti Warna Otomatis (dimWarnaAnim)
void JWS_Anim_Pro::dimWarnaAnim(int interval) {
    if (millis() - _lastDim >= interval) {
        _lastDim = millis();
        _colorIdx = (_colorIdx + 1) % 7;
        warnaGlobal = _pelangi[_colorIdx];
    }
}

// 2. Fungsi Running Text (runTextAnim)
void JWS_Anim_Pro::runTextAnim(int y, int speed, const char* teks, uint16_t warna) {
    if (millis() - _lastRun >= speed) {
        _lastRun = millis();
        
        int16_t x1, y1;
        uint16_t w, h;
        _display->setTextWrap(false);
        _display->getTextBounds(teks, 0, y, &x1, &y1, &w, &h);

        // Hapus area text lama (hanya selebar panel)
        _display->fillRect(0, y, _display->width(), 8, 0x0000); 
        
        _display->setTextColor(warna);
        _display->setCursor(_runPosX, y);
        _display->print(teks);

        _runPosX--;
        if (_runPosX < -w) { 
            _runPosX = _display->width(); 
        }
    }
}

// 3. Fungsi Pintu Kupu-Kupu (swimBoxAnim)
void JWS_Anim_Pro::swimBoxAnim(int x, int y, int w, int h, int speed, const char* teks) {
    unsigned long now = millis();
    int tengah = w / 2;

    if (now - _lastSwim >= speed) {
        _lastSwim = now;

        if (_swimStep == 0) { // MENUTUP
            _display->fillRect(x + tengah - _swimProgress, y, 1, h, 0x0000);
            _display->fillRect(x + tengah + _swimProgress, y, 1, h, 0x0000);
            _swimProgress++;
            if (_swimProgress > tengah) {
                _swimStep = 1; // Pindah ke Ganti Teks
            }
        } 
        else if (_swimStep == 1) { // UPDATE DISPLAY
            _display->fillRect(x, y, w, h, 0x0000);
            _swimStep = 2; // Langsung Buka
        }
        else if (_swimStep == 2) { // MEMBUKA
            _swimProgress--;
            _display->setTextColor(warnaGlobal);
            _display->setCursor(x + 2, y + (h/2) - 4);
            _display->print(teks);
            
            // Tutup sisi samping yang belum terbuka
            _display->fillRect(x, y, tengah - _swimProgress, h, 0x0000);
            _display->fillRect(x + tengah + _swimProgress, y, tengah - _swimProgress, h, 0x0000);

            if (_swimProgress <= 0) {
                _swimStep = 3; // Jeda Baca
                _timerWait = now + 3000; 
            }
        }
        else if (_swimStep == 3) { // WAIT
            if (now > _timerWait) {
                _swimStep = 0;
                _swimProgress = 0;
            }
        }
    }
}

// 4. Fungsi Scroll Berjenjang (scrollUpStep) - Cocok untuk Saldo
void JWS_Anim_Pro::scrollUpStep(int x, int y, int w, int h, int speed, const char* data[], int totalData) {
    unsigned long now = millis();
    int targetY = y + (h / 2) - 4;

    if (now - _lastScroll >= speed) {
        _lastScroll = now;

        if (_scrollStep == 0) { // NAIK KE TENGAH
            _display->fillRect(x, y, w, h, 0x0000);
            _display->setTextColor(warnaGlobal);
            _display->setCursor(x + 2, _currentY);
            _display->print(data[_dataIdx]);
            
            _currentY--;
            if (_currentY <= targetY) {
                _scrollStep = 1;
                _timerWait = now + 2500; // Jeda baca 2.5 detik
            }
        }
        else if (_scrollStep == 1) { // JEDA
            if (now > _timerWait) _scrollStep = 2;
        }
        else if (_scrollStep == 2) { // LANJUT NAIK SAMPAI HILANG
            _display->fillRect(x, y, w, h, 0x0000);
            _display->setCursor(x + 2, _currentY);
            _display->print(data[_dataIdx]);
            
            _currentY--;
            if (_currentY <= y - 8) {
                _dataIdx = (_dataIdx + 1) % totalData;
                _currentY = y + h; // Reset muncul dari bawah area
                _scrollStep = 0;
            }
        }
    }
}
