```diff
 .../stage3/oop/include/aggressive_strategy.h       |  14 +++++++++++
 .../stage3/oop/include/battle_strategy.h           |  17 +++++++++++++
 .../stage3/oop/include/human_factory.h             |  13 ++++++++++
 .../stage3/oop/include/orc_factory.h               |  13 ++++++++++
 .../stage3/oop/include/random_strategy.h           |  14 +++++++++++
 stages/{stage2 => stage3}/oop/include/tribe.h      |  10 +++++++-
 .../stage3/oop/include/tribe_factory.h             |  16 ++++++++++++
 stages/{stage2 => stage3}/oop/include/warrior.h    |   2 +-
 .../stage3/oop/src/aggressive_strategy.cpp         |  21 ++++++++++++++++
 .../stage3/oop/src/human_factory.cpp               |  12 +++++++++
 stages/{stage2 => stage3}/oop/src/main.cpp         |   1 +
 /dev/null => stages/stage3/oop/src/orc_factory.cpp |   6 +++++
 .../stage3/oop/src/random_strategy.cpp             |  24 ++++++++++++++++++
 stages/{stage2 => stage3}/oop/src/simulation.cpp   |  28 +++++++--------------
 stages/{stage2 => stage3}/oop/src/tribe.cpp        |  26 ++++++++++++++++++-
 stages/{stage2 => stage3}/oop/src/warrior.cpp      |  12 +++------
 stages/{stage2 => stage3}/oop/src/worker.cpp       |   6 +----
 17 files changed, 199 insertions(+), 36 deletions(-)

Only in stages/stage3/oop/include: aggressive_strategy.h
Only in stages/stage3/oop/include: battle_strategy.h
Only in stages/stage3/oop/include: human_factory.h
Only in stages/stage3/oop/include: orc_factory.h
Only in stages/stage3/oop/include: random_strategy.h
diff --color -ru stages/stage2/oop/include/tribe.h stages/stage3/oop/include/tribe.h
--- stages/stage2/oop/include/tribe.h	2026-04-13 15:34:31
+++ stages/stage3/oop/include/tribe.h	2026-05-04 17:21:16
@@ -2,7 +2,10 @@
 #define __tribe__
 
 #include <vector>
+#include <optional>
 #include "unit.h"
+#include "battle_strategy.h"
+#include "tribe_factory.h"
 
 struct SimulationContext;
 
@@ -11,14 +14,19 @@
 private:
     std::vector<std::unique_ptr<Unit>> _units;
     int _resourcesCount;
+    std::unique_ptr<TribeFactory> _factory;
+    std::unique_ptr<BattleStrategy> _strategy;
 
 public:
-    Tribe();
+    Tribe(std::unique_ptr<TribeFactory> factory, std::unique_ptr<BattleStrategy> strategy);
     void actAll(SimulationContext& context);
     void addUnit(std::unique_ptr<Unit> unit);
+    void createUnits(int count, int idOffset);
     std::optional<std::reference_wrapper<Unit>> getRandomAliveUnit();
+    std::optional<std::reference_wrapper<Unit>> getWeakestAliveUnit();
     int getResourcesCount();
     void setResourcesCount(int resources);
+    BattleStrategy& getStrategy();
 };
 
 #endif // __tribe__
\ No newline at end of file
Only in stages/stage3/oop/include: tribe_factory.h
diff --color -ru stages/stage2/oop/include/warrior.h stages/stage3/oop/include/warrior.h
--- stages/stage2/oop/include/warrior.h	2026-04-13 15:50:43
+++ stages/stage3/oop/include/warrior.h	2026-05-04 16:56:42
@@ -9,7 +9,7 @@
 public:
     int damage;
 public:
-    Warrior(int id);
+    Warrior(int id, int damage);
     void act(SimulationContext& context) override;
     void acceptAttack(UnitAttacker& attacker) override;
     void attackWarrior(Warrior& target) override;
Only in stages/stage3/oop/src: aggressive_strategy.cpp
Only in stages/stage3/oop/src: human_factory.cpp
diff --color -ru stages/stage2/oop/src/main.cpp stages/stage3/oop/src/main.cpp
--- stages/stage2/oop/src/main.cpp	2026-04-10 17:26:12
+++ stages/stage3/oop/src/main.cpp	2026-05-04 17:20:23
@@ -1,6 +1,7 @@
 #include "simulation.h"
 
 int main() {
+  srand(time(nullptr));
   const int UNIT_COUNT = 3;
   const int STEPS = 5;
 
Only in stages/stage3/oop/src: orc_factory.cpp
Only in stages/stage3/oop/src: random_strategy.cpp
diff --color -ru stages/stage2/oop/src/simulation.cpp stages/stage3/oop/src/simulation.cpp
--- stages/stage2/oop/src/simulation.cpp	2026-04-13 15:54:01
+++ stages/stage3/oop/src/simulation.cpp	2026-05-04 17:04:13
@@ -1,31 +1,21 @@
 #include "simulation.h"
 #include "simulation_context.h"
-#include "warrior.h"
-#include "worker.h"
+#include "human_factory.h"
+#include "orc_factory.h"
+#include "aggressive_strategy.h"
+#include "random_strategy.h"
 #include <iostream>
-#include <random>
 
-Simulation::Simulation(int unitCount, int steps) : _tribe1(), _tribe2() {
+Simulation::Simulation(int unitCount, int steps) 
+    : _tribe1(std::make_unique<HumanFactory>(), std::make_unique<RandomStrategy>()), 
+      _tribe2(std::make_unique<OrcFactory>(), std::make_unique<AggressiveStrategy>()) {
     _unitCount = unitCount;
     _steps = steps;
 }
 
 void Simulation::createUnits() {
-    std::random_device dev;
-    std::mt19937 rng(dev());
-    for(int i = 0; i < _unitCount; ++i)
-    {
-        std::uniform_int_distribution<std::mt19937::result_type> dist6(0,1);
-        // The same type of unit is added to both tribes at once
-        if(dist6(rng)) {
-            _tribe1.addUnit(std::make_unique<Warrior>(i));
-            _tribe2.addUnit(std::make_unique<Warrior>(i+_unitCount));
-        }
-        else {
-            _tribe1.addUnit(std::make_unique<Worker>(i));
-            _tribe2.addUnit(std::make_unique<Worker>(i+_unitCount));
-        }
-    }
+    _tribe1.createUnits(_unitCount, 0);
+    _tribe2.createUnits(_unitCount, _unitCount);
 }
 
 void Simulation::run() {
diff --color -ru stages/stage2/oop/src/tribe.cpp stages/stage3/oop/src/tribe.cpp
--- stages/stage2/oop/src/tribe.cpp	2026-04-13 15:54:21
+++ stages/stage3/oop/src/tribe.cpp	2026-05-04 17:08:58
@@ -8,7 +8,8 @@
 #include <utility>
 #include <vector>
 
-Tribe::Tribe() {
+Tribe::Tribe(std::unique_ptr<TribeFactory> factory, std::unique_ptr<BattleStrategy> strategy) 
+    : _factory(std::move(factory)), _strategy(std::move(strategy)) {
     _resourcesCount = 0;
 }
 
@@ -23,6 +24,12 @@
     }
 }
 
+void Tribe::createUnits(int count, int idOffset) {
+    for (int i = 0; i < count; ++i) {
+        addUnit(_factory->createUnit(idOffset + i));
+    }
+}
+
 std::optional<std::reference_wrapper<Unit>> Tribe::getRandomAliveUnit() {
     // Two passes: first we count the live ones, then we go to the desired one.
     // Does not require an additional buffer.
@@ -44,10 +51,27 @@
     return std::nullopt;
 }
 
+std::optional<std::reference_wrapper<Unit>> Tribe::getWeakestAliveUnit() {
+    Unit* weakest = nullptr;
+    int minHealth = INT_MAX;
+    for (auto& unit : _units) {
+        if(unit->isAlive() && unit->getHealth() < minHealth) {
+            minHealth = unit->getHealth();
+            weakest = unit.get();
+        }
+    }
+    if(weakest == nullptr) return std::nullopt;
+    return *weakest;
+}
+
 int Tribe::getResourcesCount() {
     return _resourcesCount;
 }
 
 void Tribe::setResourcesCount(int resources) {
     _resourcesCount = std::max(resources, 0);
+}
+
+BattleStrategy& Tribe::getStrategy() {
+    return *_strategy;
 }
\ No newline at end of file
diff --color -ru stages/stage2/oop/src/warrior.cpp stages/stage3/oop/src/warrior.cpp
--- stages/stage2/oop/src/warrior.cpp	2026-04-13 15:21:15
+++ stages/stage3/oop/src/warrior.cpp	2026-05-04 17:01:49
@@ -1,21 +1,15 @@
 #include <iostream>
-#include <optional>
 #include "warrior.h"
 #include "simulation_context.h"
 #include "tribe.h"
 #include "worker.h"
 
-Warrior::Warrior(int id) : Unit(id) {
-    damage = 35;
+Warrior::Warrior(int id, int damage) : Unit(id) {
+    this->damage = damage;
 }
 
 void Warrior::act(SimulationContext& context) {
-    auto target = context.enemyTribe.get().getRandomAliveUnit();
-    if(target == std::nullopt) {
-        std::cout << "Warrior " << id << " didn't find enemy to attack\n";
-        return;
-    }
-    target->get().acceptAttack(*this);
+    context.ownTribe.get().getStrategy().actWarrior(*this, context);
 }
 
 void Warrior::acceptAttack(UnitAttacker& attacker) {
diff --color -ru stages/stage2/oop/src/worker.cpp stages/stage3/oop/src/worker.cpp
--- stages/stage2/oop/src/worker.cpp	2026-04-13 15:04:31
+++ stages/stage3/oop/src/worker.cpp	2026-05-04 17:05:12
@@ -1,4 +1,3 @@
-#include <iostream>
 #include "worker.h"
 #include "simulation_context.h"
 #include "tribe.h"
@@ -6,10 +5,7 @@
 Worker::Worker(int id) : Unit(id) {}
 
 void Worker::act(SimulationContext& context) {
-    int foundResources = rand() % 10;
-    auto& ownTribe = context.ownTribe.get();
-    ownTribe.setResourcesCount(foundResources + ownTribe.getResourcesCount());
-    std::cout << "Worker " << id << " found: " << foundResources << "; now have " << ownTribe.getResourcesCount() << "\n";
+    context.ownTribe.get().getStrategy().actWorker(*this, context);
 }
 
 void Worker::acceptAttack(UnitAttacker& attacker) {
```