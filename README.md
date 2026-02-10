# Zad_Test_Interakcja

Projekt testowy wykonany w **Unreal Engine 5** demonstrujący system **interakcji gracza z obiektami**, komunikację między modułami oraz integrację **C++ ↔ Blueprint ↔ UMG**.

---

1. Wymagania:
   - **Unreal Engine 5.7** (lub kompatybilna wersja UE5)
   - **Visual Studio 2022** z:
     - MSVC v143
     - Windows 10/11 SDK
     - C++ Game Development workload

2. Uruchom grę:
   - Tryb **Play In Editor**
   - Najlepiej: **Selected Viewport**
  
## 🎮 Sterowanie

| Akcja                         | Klawisz / Wejście |
|--------------------------------|-------------------|
| Ruch                           | W / A / S / D     |
| Obrót kamery                   | Mysz              |
| Interakcja z obiektem          | E na klawiaturze  |
| Podniesienie przedmiotu        | E na klawiaturze  |

Podchodzimy do jednej z ścian, nakierowujemy myszką na placeholderową broń, klikamy przycisk E (ustawiamy broń na aktywną)
Następnie podchodzimy do jednej z skrzynek leżących na podestach i klikamy przycisk E (dostajemy bonus amunicji do broni)

*(Dokładne mapowanie wejścia realizowane przez Enhanced Input)*

### Główne założenia
- Architektura **modułowa** logika rozdzielona na moduły
- Rozdzielenie:
  - Interakcje (Pickable)
  - Aktorzy (Gracz)
  - UI (UI Interakcji, UI Broni)
  - Core (podstawowe struktury / klasy )
- Komunikacja oparta o **eventy / delegaty** między warstwą C++ a Blueprintami
- Możliwość łatwej rozbudowy o nowe typy interakcji i przedmiotów 
(dziedziczenie Blueprintu BP_Pickable_Ammo dla pick-upów amunicji)
, (dziedziczenie Blueprintu BP_Pickable_Weapon dla nowych broni)
- Metody obliczające raycasty lub ekwipunek gracza wykonane w C++,
w Blueprintach zaimplementowana logika uruchamiająca i wykonująca

### Ograniczenia
- Pickupy i Bronie nie znikają, dla celów testowych są widoczne cały czas.
- Brak możliwości "strzelania" z bronii
- UI Interakcji nie dostosowuje się do rozmiaru tekstu
- Brak potwierdzenia interakcji z bronią / amunicją

## Wykonana Praca

### C++
- Kalkulacja interakcji z pickupami
- System ekwipunku
- Podstawa systemu UI
- Sterowanie Gracza
### Blueprints
- UI Interakcji i panelu bronii
- Aplikowanie wartości zmiennych do widoków UI
- Logika uruchamiająca / decydująca interakcje z obiektami
- Blueprinty Pick-upów i ich ustawienie wartości
