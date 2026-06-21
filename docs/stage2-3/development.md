# Процесс разработки
## Расы и поведение:
У каждого племени теперь есть две новые характеристики: **раса** и **поведение**. 
**Раса** определяет состав племени. Реализовано 2 расы:
- `HumanFactory` создаёт случайную смесь `Warrior`(damage = 35) и `Worker`.
- `OrcFactory` создаёт только `Warrior`(damage = 50).

Также реализованы 2 типа поведения:
- `RandomStrategy` атакует случайного врага, рабочие добывают ресурсы.
- `AggressiveStrategy` атакует самого слабого врага, рабочие ничего не делают.

## Конкретные реализации:
### ООП
**Фабричный метод:** Базовый класс `TribeFactory` с одним методом `createUnit(int id)`. Наследники `HumanFactory` и `OrcFactory` решают сами, что создавать.

**Стратегия + Посетитель:** `BattleStrategy` имеет два метода — `actWarrior` и `actWorker`, один из которых в зависимости от конкретного типа `Unit` вызывается из классов-наследников `Unit`. Получается ещё один **Visitor**.
Цепочка вызовов:
```cpp
warrior.act(context)
    context.ownTribe.getStrategy().actWarrior(*this, context)
        target.acceptAttack(*this)
            attacker.attackWarrior(target)
```

Цепочка теперь имеет три уровня диспетчеризации. Это «паттерн на паттерне».

### ППП
**Фабричный метод + Мультиметод:** `TribeFactory` — обобщение, `factory_create_unit<TribeFactory* f>(int id)` — параметрическая функция.

**Стратегия + двойная диспетчеризация:** `strategy_execute<BattleStrategy* s, Unit* unit>` - мультиметод, что позволяет избежать Visitor внутри Strategy:
```c
void strategy_execute<BattleStrategy.aggressive* s, Unit.warrior* unit>(...);
void strategy_execute<BattleStrategy.random* s, Unit.worker* unit>(...);
```
Один вызов `strategy_execute<strategy, (Unit*)unit>(context)` диспетчеризуется по обоим типам одновременно.

**Цепочка вызовов:**
```c
unit_act<warrior>(context)
    strategy_execute<strategy, warrior>(context)
        warrior_attack<warrior, target>()
```

## Другие изменения:
- В `Tribe` добавлено владение фабрикой и стратегией. 
- Метод `createUnits` перенесён из `Simulation` в `Tribe` и теперь использует свою фабрику. 
- Добавлен метод `getWeakestAliveUnit` для агрессивной стратегии. 
- Конструктор `Warrior` теперь принимает `damage` параметром.