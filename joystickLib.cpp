#include "joystickLib.h"

EntprellterTaster::EntprellterTaster(int tasterPin, int xPin, int yPin) 
  : pin(tasterPin), xPin(xPin), yPin(yPin), entprellterZustand(false), 
    letzteAenderung(0), druckBeginn(0), gedruecktGemeldet(true) {
  pinMode(pin, INPUT_PULLUP);
}

void EntprellterTaster::aktualisiere() {
  bool aktuellerZustand = !digitalRead(pin);
  
  unsigned long aktuelleZeit = millis();
  
  if (aktuellerZustand != entprellterZustand && (aktuelleZeit - letzteAenderung) > entprellZeit) {
    entprellterZustand = aktuellerZustand;
    letzteAenderung = aktuelleZeit;
    
    if (entprellterZustand) {
      druckBeginn = aktuelleZeit;
      gedruecktGemeldet = false;
    }
  }
}

bool EntprellterTaster::istGedrueckt() {
  return entprellterZustand;
}

bool EntprellterTaster::wurdeGedrueckt() {
  if (!entprellterZustand && !gedruecktGemeldet) {
    if (millis() - druckBeginn < langeDruckZeit) {
      gedruecktGemeldet = true;
      return true;
    }
  }
  return false;
}

bool EntprellterTaster::wurdeLangeGedrueckt() {
  if (entprellterZustand && !gedruecktGemeldet) {
    if (millis() - druckBeginn >= langeDruckZeit) {
      gedruecktGemeldet = true;
      return true;
    }
  }
  return false;
}

int EntprellterTaster::leseX() {
  return analogRead(xPin);
}

int EntprellterTaster::leseY() {
  return analogRead(yPin);
}