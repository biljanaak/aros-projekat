# Barbershop Problem

Ovaj projekat implementira poznati problem "Barbershop Problem" koristeći C jezik. 
Problem modeluje situaciju u frizerskom salonu sa ograničenim brojem stolica i frizerom koji uslužuje mušterije.

## Kako radi?

Program simulira ponašanje frizera i mušterija u salonu:

- Frizer čeka da mušterija dođe i uslužuje je ako ima slobodnih stolica.
- Mušterije dolaze u salon i čekaju ako ima slobodnih stolica, u suprotnom odlaze.

## Instalacija i Pokretanje

Da kompajlirate program, koristite priloženi `Makefile`. U terminalu pokrenite:

```bash
make
```

Ova komanda će generisati izvršni fajl `barber.out`.

### Pokretanje

Pokrenite program sa:

```bash
./barber.out
```

### Struktura Koda

- `frizerFunkcija()`: Simulira rad frizera.
- `musterijaFunkcija()`: Simulira dolazak mušterija u salon.
- Sinhronizacija je ostvarena pomoću semafora i mutexa.
