# ⚡ Reaction Game – دوئل واکنش (Reaction Duel)

<div align="center">
  
  [**English**](#english) | [**فارسی**](#persian)
  
</div>

---

<a name="english"></a>
## 📖 Description (English)

This is a **two‑player reaction game** built with Arduino. Two players each have a button. A white LED lights up after a random delay (2‑6 seconds). The first player to press their button **wins** – their red LED lights up and a victory melody plays. If any player presses **before** the white LED turns on, both lose (false start) – red LEDs flash and an alarm sounds. Background music plays throughout the game, and the round automatically restarts after each result.

### Features
- Two‑player reaction duel (buttons on pins 13 and 8)
- Random delay (2‑6 seconds) before the “go” signal (white LED)
- False start detection – pressing before white LED results in loss for both
- Visual feedback: white LED (wait/start), individual red LEDs for each player
- Audio feedback: buzzer with start tone, win melody, false‑start alarm
- Continuous background music (stored in PROGMEM) that never blocks the game
- Automatic round reset – game restarts after win or loss

### Components Required
- Arduino board (Uno, Nano, etc.)
- 2 push buttons (normally open)
- 1 white LED + 220Ω resistor
- 2 red LEDs (one per player) + 220Ω resistors
- 1 passive buzzer (or active buzzer – change tone behaviour)
- Jumper wires & breadboard
- Power supply (USB or battery)

### Wiring Diagram

| Component | Arduino Pin |
|-----------|-------------|
| Button 1 (Player 1) | 13 (INPUT_PULLUP) |
| Button 2 (Player 2) | 8 (INPUT_PULLUP) |
| White LED (+) | 11 (via 220Ω resistor) |
| White LED (-) | GND |
| Red LED 1 (Player 1) (+) | 12 (via 220Ω resistor) |
| Red LED 2 (Player 2) (+) | 9 (via 220Ω resistor) |
| Both red LED cathodes | GND |
| Buzzer (+) | 10 |
| Buzzer (-) | GND |

> **Note:** Buttons use internal pull‑up resistors (`INPUT_PULLUP`). Connect one button leg to the pin, the other leg to **GND**. No external resistors needed.

### How to Play
1. **Upload** the code to Arduino.
2. The background music starts playing immediately.
3. The game waits for a **random delay** (2–6 seconds). During this time:
   - The white LED is **OFF**.
   - If any player presses their button, it’s a **false start** → both red LEDs flash, alarm sounds, and the round restarts.
4. After the random delay, the **white LED turns ON** and a short beep sounds.
5. The first player to press their button after the white LED **wins**:
   - That player’s red LED lights up.
   - A victory melody plays.
6. After win or loss, the round **automatically resets** (white LED off, red LEDs off, new random delay).

### Game Logic Explained
- `randomDelayTime` = current time + random(2000, 6000) milliseconds.
- In `loop()`:
  - If game not started and not finished, check button presses → if any pressed, call `lose()`.
  - When `millis()` reaches `randomDelayTime`, turn on white LED, play start sound, set `gameStarted = true`.
  - If game started and not finished, the first button press calls `win(player)`.
- `win()`: lights corresponding red LED, plays victory beeps, calls `startNewRound()`.
- `lose()`: flashes both red LEDs, plays alarm, calls `startNewRound()`.
- `startNewRound()`: resets all LEDs, clears flags, generates new random delay.
- Background music plays continuously using non‑blocking timing (`millis()`), independent of game state.

### Custom Characters? Not here – but we have **Melody in PROGMEM**
The background melody is stored in **PROGMEM** (flash memory) to save RAM. The melody array contains pairs of (note, duration). The music playback is non‑blocking, so it never interferes with button reading or game timing.

### Code Structure
- `playBackgroundMusic()` – called every loop, uses `millis()` to play notes sequentially.
- `win(int player)` and `lose(int player)` – handle end‑of‑round actions.
- `startNewRound()` – resets the game state and sets a new random delay.
- Buttons are read using `digitalRead()` with pull‑ups (pressed = LOW).

### Customization Ideas
- **Change reaction delay range:** modify `random(2000, 6000)` in `startNewRound()`.
- **Change victory melody:** edit the `melody[]` array (format: NOTE, duration, ...).
- **Add score tracking:** store wins for each player and display on Serial Monitor or an LCD.
- **Use active buzzer:** replace `tone()` with `digitalWrite()` to turn buzzer on/off (for simple beeps).
- **Add a start button:** require an extra button to begin each round instead of auto‑reset.

### Troubleshooting
- **Buttons not responding:** ensure you connected the button to GND and the pin, not to VCC. `INPUT_PULLUP` expects GND when pressed.
- **Buzzer sounds weird:** if using an active buzzer, `tone()` may not work well – use `digitalWrite(buzzerPin, HIGH)` for beeps instead.
- **White LED flashes briefly at start:** normal – it turns on at the exact moment `randomDelayTime` is reached.
- **Game resets too quickly:** increase the delay in `win()`/`lose()` before calling `startNewRound()`.

### License
MIT License – free to use, modify, and distribute.

---

<a name="persian"></a>
## 📖 توضیحات (فارسی)

این پروژه یک **بازی عکس‌العملی دو نفره** است که با Arduino ساخته شده. هر بازیکن یک دکمه دارد. بعد از یک تأخیر تصادفی (۲ تا ۶ ثانیه) یک LED سفید روشن می‌شود. اولین بازیکنی که دکمه خود را فشار دهد **برنده** است – LED قرمز مخصوص او روشن می‌شود و ملودی پیروزی پخش می‌شود. اگر هر بازیکنی **قبل از روشن شدن LED سفید** دکمه را فشار دهد، هر دو می‌بازند (شروع زودهنگام) – هر دو LED قرمز چشمک می‌زنند و صدای اخطار پخش می‌شود. موسیقی زمینه در تمام طول بازی پخش می‌شود و راند به طور خودکار پس از هر نتیجه مجدداً شروع می‌شود.

### امکانات
- دوئل عکس‌العملی دو نفره (دکمه‌ها روی پایه‌های ۱۳ و ۸)
- تأخیر تصادفی (۲ تا ۶ ثانیه) قبل از علامت «برو» (LED سفید)
- تشخیص شروع زودهنگام – فشار دکمه قبل از LED سفید باعث باخت هر دو می‌شود
- بازخورد بصری: LED سفید (منتظر/شروع)، LED قرمز جداگانه برای هر بازیکن
- بازخورد صوتی: بوق با صدای شروع، ملودی برد، اخطار شروع زودهنگام
- موسیقی زمینه پیوسته (ذخیره شده در PROGMEM) که هرگز بازی را متوقف نمی‌کند
- شروع مجدد خودکار راند – بازی پس از برد یا باخت دوباره شروع می‌شود

### قطعات مورد نیاز
- برد Arduino (Uno، Nano یا مشابه)
- ۲ عدد دکمه فشاری (معمولاً باز)
- ۱ عدد LED سفید + مقاومت ۲۲۰ اهم
- ۲ عدد LED قرمز (یکی برای هر بازیکن) + مقاومت‌های ۲۲۰ اهم
- ۱ عدد بوق غیرفعال (یا فعال – در این صورت رفتار تابع tone متفاوت است)
- برد بورد و سیم جامپر
- منبع تغذیه (USB یا باتری)

### نقشه اتصالات

| قطعه | پین آردوینو |
|------|--------------|
| دکمه ۱ (بازیکن ۱) | ۱۳ (INPUT_PULLUP) |
| دکمه ۲ (بازیکن ۲) | ۸ (INPUT_PULLUP) |
| LED سفید (+) | ۱۱ (از طریق مقاومت ۲۲۰ اهم) |
| LED سفید (-) | GND |
| LED قرمز ۱ (بازیکن ۱) (+) | ۱۲ (از طریق مقاومت ۲۲۰ اهم) |
| LED قرمز ۲ (بازیکن ۲) (+) | ۹ (از طریق مقاومت ۲۲۰ اهم) |
| کاتد هر دو LED قرمز | GND |
| بوق (+) | ۱۰ |
| بوق (-) | GND |

> **نکته:** دکمه‌ها از مقاومت بالاکش داخلی استفاده می‌کنند (`INPUT_PULLUP`). یک پایه دکمه به پین آردوینو، پایه دیگر به **GND** وصل می‌شود. مقاومت خارجی نیاز نیست.

### نحوه بازی کردن
1. **کد** را روی Arduino آپلود کنید.
2. موسیقی زمینه بلافاصله شروع به پخش می‌کند.
3. بازی منتظر یک **تأخیر تصادفی** (۲ تا ۶ ثانیه) می‌ماند. در این مدت:
   - LED سفید **خاموش** است.
   - اگر هر بازیکنی دکمه خود را فشار دهد، **شروع زودهنگام** رخ می‌دهد → هر دو LED قرمز چشمک می‌زنند، صدای اخطار پخش می‌شود و راند مجدداً شروع می‌شود.
4. پس از تأخیر تصادفی، **LED سفید روشن می‌شود** و یک بوق کوتاه به صدا درمی‌آید.
5. اولین بازیکنی که بعد از روشن شدن LED سفید دکمه خود را فشار دهد **برنده** می‌شود:
   - LED قرمز همان بازیکن روشن می‌شود.
   - ملودی پیروزی پخش می‌شود.
6. پس از برد یا باخت، راند **به طور خودکار مجدداً شروع می‌شود** (LED سفید خاموش، LED‌های قرمز خاموش، تأخیر تصادفی جدید).

### منطق بازی
- `randomDelayTime` = زمان فعلی + مقدار تصادفی بین ۲۰۰۰ تا ۶۰۰۰ میلی‌ثانیه.
- در `loop()`:
  - اگر بازی شروع نشده و تمام نشده، فشار دکمه‌ها را بررسی کن → اگر هر کدام فشرده شد، تابع `lose()` را صدا بزن.
  - وقتی `millis()` به `randomDelayTime` رسید، LED سفید را روشن کن، صدای شروع را پخش کن، `gameStarted = true` را تنظیم کن.
  - اگر بازی شروع شده و تمام نشده، اولین دکمه فشرده شده تابع `win(player)` را صدا می‌زند.
- `win()`: LED قرمز متناظر را روشن می‌کند، بوق‌های پیروزی را پخش می‌کند، `startNewRound()` را صدا می‌زند.
- `lose()`: هر دو LED قرمز را چشمک می‌زند، صدای اخطار پخش می‌کند، `startNewRound()` را صدا می‌زند.
- `startNewRound()`: همه LED‌ها را خاموش می‌کند، پرچم‌ها را پاک می‌کند، تأخیر تصادفی جدید تولید می‌کند.
- موسیقی زمینه به طور پیوسته و بدون بلوکه شدن (با `millis()`) و مستقل از وضعیت بازی پخش می‌شود.

### ملودی در PROGMEM
ملودی زمینه در حافظه **PROGMEM** (فلش) ذخیره شده تا RAM اشغال نشود. آرایه `melody` شامل جفت‌های (نت، مدت‌زمان) است. پخش موسیقی غیر‑مسدود بوده و هرگز با خواندن دکمه یا زمان‌بندی بازی تداخل ندارد.

### ساختار کد
- `playBackgroundMusic()` – در هر بار اجرای `loop` فراخوانی می‌شود، با `millis()` نت‌ها را پشت سر هم پخش می‌کند.
- `win(int player)` و `lose(int player)` – اقدامات پایان راند را انجام می‌دهند.
- `startNewRound()` – وضعیت بازی را بازنشانی کرده و تأخیر تصادفی جدید تعیین می‌کند.
- دکمه‌ها با `digitalRead()` و pull‑up خوانده می‌شوند (فشرده شدن = LOW).

### ایده‌های سفارشی‌سازی
- **تغییر محدوده تأخیر واکنش:** مقدار `random(2000, 6000)` را در `startNewRound()` تغییر دهید.
- **تغییر ملودی برد:** آرایه `melody[]` را ویرایش کنید (فرمت: NOTE, duration, ...).
- **اضافه کردن ثبت امتیاز:** بردهای هر بازیکن را ذخیره کرده و روی Serial Monitor یا LCD نمایش دهید.
- **استفاده از بوق فعال (Active Buzzer):** به جای `tone()` از `digitalWrite()` برای خاموش/روشن کردن بوق استفاده کنید (برای بوق‌های ساده).
- **اضافه کردن دکمه شروع:** برای شروع هر راند یک دکمه جداگانه تعریف کنید به جای شروع خودکار.

### عیب‌یابی
- **دکمه‌ها کار نمی‌کنند:** مطمئن شوید دکمه به GND وصل شده است نه VCC. `INPUT_PULLUP` انتظار LOW هنگام فشار را دارد.
- **صدای بوق نامناسب است:** اگر از بوق فعال (active) استفاده می‌کنید، `tone()` ممکن است خوب کار نکند – به جای آن برای بوق‌های ساده از `digitalWrite(buzzerPin, HIGH)` استفاده کنید.
- **LED سفید برای لحظه‌ای چشمک می‌زند:** طبیعی است – درست در لحظه رسیدن به `randomDelayTime` روشن می‌شود.
- **بازی太快 (خیلی سریع) ریست می‌شود:** مقدار تأخیر داخل `win()`/`lose()` را قبل از فراخوانی `startNewRound()` افزایش دهید.

### مجوز
مجوز MIT – آزاد برای استفاده، تغییر و توزیع.

---

**Enjoy the reaction duel! ⚡**  
**از دوئل عکس‌العملی لذت ببرید!**
