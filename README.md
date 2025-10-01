### Збирання:
```bash
g++ -std=gnu++20 -O2 -Wall -Wextra -pedantic \
  src/main.cpp src/ChaosGame.cpp \
  -I include -o chaos_game
```

### Запуск:
```bash
./chaos_game input.txt output.txt
# або з фіксованим зерном ГВЧ (для відтворюваності):
./chaos_game input.txt output.txt 12345
```

