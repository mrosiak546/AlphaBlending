# AlphaBlending
Projekt Alpha Blending na przedmiot Grafika Komputerowa

# Projekt Alpha Blending
Projekt ten pozwala nam na mieszanie kanałów alpha przy użyciu frameworka QT. Mieszanie alpha jest to technika używana w grafice komputerowej do łączenia wielu warstw
obrazów. Aplikacja umożliwia wczytanie trzech obrazów, dostososowywanie ich trybów mieszania oraz kontrolowanie wartości alfa.

# Tryby Mieszania
- **Normal (`buttonNormal`):**
  - Standardowy tryb mieszania alpha, gdzie kolor pierwszoplanowy jest mieszany z kolorem tła na podstawie wartości alfa
- **Multiply (`buttonMultiply`):**
  - Wynik to iloczyn kolorów pierwszoplanowego i tła, co prowadzi do ciemniejszego obrazu
- **Screen (`buttonScreen`):**
  - Wynik to odwrotność iloczynu odwrotności kolorów pierwszoplanowego i tła, co prowadzi do jaśniejszego obrazu.
- **Darken (`buttonDarken`):**
  - Wynik to minimalna wartość kolorów pierwszoplanowego i tła co prowadzi do ciemniejszego obrazu
- **Lighten (`buttonLighten`):**
  - Wynik to Maksymalna wartość kolorów pierwszoplanowego i tła, co prowadzi do jaśniejszego obrazu

 # Użycie
 1. Ustaw ścieżki w kodzie do obrazków jakie chcesz wczytać
 2. Uruchom aplikacje
 3. Dostosuj tryby mieszania za pomocą przycisków
 4. Za pomocą suwaków kontroluj każdą warstwę i obserwuj zachodzące zmiany
