# OOP vs PPP: Evolutionary Game Experiment
# Русскоязычная версия:
Проект посвящён поэтапному сравнению объектно-ориентированного (OOP)
и процедурно-параметрического (PPP) подходов.

Каждая стадия представляет собой одинаковое расширение игрового
сценария, реализованное двумя способами и сопровождаемое метриками.

## Сборка и запуск проекта
Использование Docker для PPP сборки включено по-умолчанию.
Стадии нумеруются как stage0, stage1, ...
### Для OOP:

```
make build MODE=oop STAGE=stageN
make run MODE=oop STAGE=stageN
```
### Для PPP:
```
make build MODE=ppp STAGE=stageN USE_DOCKER=[yes/no]
make run MODE=ppp STAGE=stageN USE_DOCKER=[yes/no]
```

## Работа над проектом
### Git
Примеры правильных заголовков коммитов
```
[stage-1][scenario] add stage-1
[stage-1][oop] upd Unit to virtual act()
[stage-1][ppp] fix specialization for act()
[common] upd README.md
```