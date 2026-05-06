```diff
 .../stage3/ppp/include/aggressive_strategy.h       |  16 +++++++++++
 .../stage3/ppp/include/battle_strategy.h           |  15 ++++++++++
 .../stage3/ppp/include/human_factory.h             |  13 +++++++++
 .../stage3/ppp/include/orc_factory.h               |  13 +++++++++
 .../stage3/ppp/include/random_strategy.h           |  16 +++++++++++
 stages/{stage2 => stage3}/ppp/include/tribe.h      |   8 +++++-
 .../stage3/ppp/include/tribe_factory.h             |  12 ++++++++
 stages/{stage2 => stage3}/ppp/include/warrior.h    |   3 +-
 .../stage3/ppp/src/aggressive_strategy.c           |  21 ++++++++++++++
 .../stage3/ppp/src/battle_strategy.c               |   5 ++++
 /dev/null => stages/stage3/ppp/src/human_factory.c |  16 +++++++++++
 stages/{stage2 => stage3}/ppp/src/main.c           |   1 +
 /dev/null => stages/stage3/ppp/src/orc_factory.c   |  10 +++++++
 .../stage3/ppp/src/random_strategy.c               |  21 ++++++++++++++
 stages/{stage2 => stage3}/ppp/src/simulation.c     |  27 ++++++-----------
 stages/{stage2 => stage3}/ppp/src/tribe.c          |  32 ++++++++++++++++++++-
 /dev/null => stages/stage3/ppp/src/tribe_factory.c |   7 +++++
 stages/{stage2 => stage3}/ppp/src/warrior.c        |  13 ++++-----
 stages/{stage2 => stage3}/ppp/src/worker.c         |   5 +++-
 19 files changed, 224 insertions(+), 30 deletions(-)

Only in stages/stage3/ppp/include: aggressive_strategy.h
Only in stages/stage3/ppp/include: battle_strategy.h
Only in stages/stage3/ppp/include: human_factory.h
Only in stages/stage3/ppp/include: orc_factory.h
Only in stages/stage3/ppp/include: random_strategy.h
diff --color -ru stages/stage2/ppp/include/tribe.h stages/stage3/ppp/include/tribe.h
--- stages/stage2/ppp/include/tribe.h	2026-04-13 16:00:27
+++ stages/stage3/ppp/include/tribe.h	2026-05-06 14:16:03
@@ -4,16 +4,22 @@
 #include "simulation_context.h"
 #include "unit.h"
 #include "container.h"
+#include "battle_strategy.h"
+#include "tribe_factory.h"
 
 typedef struct SimulationContext SimulationContext;
 
 // tribe.h - a tribe is like a collection of units with common resources(opaque pointer)
 typedef struct Tribe Tribe;
 
-Tribe* tribe_create(int unit_count);
+Tribe* tribe_create(int unit_count, TribeFactory* factory, BattleStrategy* strategy);
 void tribe_add(Tribe* tribe, Unit* unit);
+// creates units using bound factory
+void tribe_create_units(Tribe* tribe, int count, int id_offset);
 void tribe_act_all(Tribe* tribe, SimulationContext* context);
 Unit* get_random_alive_unit(Tribe* tribe);
+Unit* get_weakest_alive_unit(Tribe* tribe);
+BattleStrategy* tribe_get_strategy(Tribe* tribe);
 void tribe_destroy(Tribe* tribe);
 
 #endif // __tribe__
Only in stages/stage3/ppp/include: tribe_factory.h
diff --color -ru stages/stage2/ppp/include/warrior.h stages/stage3/ppp/include/warrior.h
--- stages/stage2/ppp/include/warrior.h	2026-04-13 16:07:11
+++ stages/stage3/ppp/include/warrior.h	2026-05-06 14:16:46
@@ -13,7 +13,8 @@
 
 Unit + <warrior: Warrior;>;
 
-Unit* warrior_create(int id);
+Unit* warrior_create(int id, int damage);
+void warrior_attack<Unit* attacker, Unit* target>();
 // multimethod to attack warrior. Damage is halved due to armor
 // damage * 0.5 is an integer truncation
 void warrior_attack<Unit.warrior* attacker, Unit.warrior* target>();
Only in stages/stage3/ppp/src: aggressive_strategy.c
Only in stages/stage3/ppp/src: battle_strategy.c
Only in stages/stage3/ppp/src: human_factory.c
diff --color -ru stages/stage2/ppp/src/main.c stages/stage3/ppp/src/main.c
--- stages/stage2/ppp/src/main.c	2026-04-10 17:26:57
+++ stages/stage3/ppp/src/main.c	2026-05-06 14:18:23
@@ -3,6 +3,7 @@
 #include <stdlib.h>
 
 int main(void) {
+    srand(time(NULL));
     const int UNIT_COUNT = 3;
     const int STEPS = 5;
     srand(time(NULL));
Only in stages/stage3/ppp/src: orc_factory.c
Only in stages/stage3/ppp/src: random_strategy.c
diff --color -ru stages/stage2/ppp/src/simulation.c stages/stage3/ppp/src/simulation.c
--- stages/stage2/ppp/src/simulation.c	2026-04-13 16:04:48
+++ stages/stage3/ppp/src/simulation.c	2026-05-06 14:17:37
@@ -2,6 +2,10 @@
 #include "tribe.h"
 #include "warrior.h"
 #include "worker.h"
+#include "aggressive_strategy.h"
+#include "random_strategy.h"
+#include "human_factory.h"
+#include "orc_factory.h"
 #include <stdlib.h>
 
 struct Simulation {
@@ -13,8 +17,8 @@
 
 Simulation* simulation_create(int unit_count, int steps) {
     Simulation* sim = malloc(sizeof(Simulation));
-    Tribe* tribe1 = tribe_create(unit_count);
-    Tribe* tribe2 = tribe_create(unit_count);
+    Tribe* tribe1 = tribe_create(unit_count, human_factory_create(), random_strategy_create());
+    Tribe* tribe2 = tribe_create(unit_count, orc_factory_create(), aggressive_strategy_create());
     sim->tribe1 = tribe1;
     sim->tribe2 = tribe2;
     sim->steps = steps;
@@ -23,22 +27,9 @@
 }
 
 void simulation_add_units(Simulation* sim) {
-    for(int i = 0; i < sim->unit_count; ++i) {
-        int rand_unit = rand() % 2;
-        // The same type of unit is added to both tribes at once
-        if(rand_unit == 1) {
-            Unit* u1 = worker_create(i);
-            Unit* u2 = worker_create(i+sim->unit_count);
-            tribe_add(sim->tribe1, u1);
-            tribe_add(sim->tribe2, u2);
-        }
-        else {
-            Unit* u1 = warrior_create(i);
-            Unit* u2 = warrior_create(i+sim->unit_count);
-            tribe_add(sim->tribe1, u1);
-            tribe_add(sim->tribe2, u2);
-        }
-    }
+    // Each tribe uses its own factory to populate units
+    tribe_create_units(sim->tribe1, sim->unit_count, 0);
+    tribe_create_units(sim->tribe2, sim->unit_count, sim->unit_count);
 }
 
 void simulation_run(Simulation* sim) {
diff --color -ru stages/stage2/ppp/src/tribe.c stages/stage3/ppp/src/tribe.c
--- stages/stage2/ppp/src/tribe.c	2026-04-13 16:05:57
+++ stages/stage3/ppp/src/tribe.c	2026-05-06 14:17:55
@@ -1,16 +1,21 @@
 #include <stdio.h>
 #include <stdlib.h>
+#include <limits.h>
 
 #include "tribe.h"
 
 struct Tribe {
     struct ppVector.unit units;
     int unit_count;
+    BattleStrategy* strategy;
+    TribeFactory* factory;
 };
 
-Tribe* tribe_create(int unit_count) {
+Tribe* tribe_create(int unit_count, TribeFactory* factory, BattleStrategy* strategy) {
     Tribe* t = malloc(sizeof(Tribe));
     t->unit_count = 0;
+    t->factory = factory;
+    t->strategy = strategy;
     ppVector_INIT(t->units);
     return t;
 }
@@ -20,6 +25,13 @@
     t->unit_count++;
 }
 
+void tribe_create_units(Tribe* tribe, int count, int id_offset) {
+    for(int i = 0; i < count; ++i) {
+        Unit* u = factory_create_unit<tribe->factory>(id_offset + i);
+        tribe_add(tribe, u);
+    }
+}
+
 void tribe_act_all(Tribe* tribe, SimulationContext* context) {
     for (int i = 0; i < tribe->unit_count; ++i) {
         Unit* u;
@@ -55,6 +67,24 @@
         target--;
     }
     return NULL;
+}
+
+Unit* get_weakest_alive_unit(Tribe* tribe) {
+    Unit* weakest = NULL;
+    int min_health = INT_MAX;
+    for(int i = 0; i < tribe->unit_count; ++i) {
+        Unit* u;
+        ppVector_GET_VAL_INDEX(u, tribe->units, i);
+        if(is_alive(u) && get_health(u) < min_health) {
+            min_health = get_health(u);
+            weakest = u;
+        }
+    }
+    return weakest;
+}
+
+BattleStrategy* tribe_get_strategy(Tribe* tribe) {
+    return tribe->strategy;
 }
 
 void tribe_destroy(Tribe* tribe) {
Only in stages/stage3/ppp/src: tribe_factory.c
diff --color -ru stages/stage2/ppp/src/warrior.c stages/stage3/ppp/src/warrior.c
--- stages/stage2/ppp/src/warrior.c	2026-04-13 15:03:25
+++ stages/stage3/ppp/src/warrior.c	2026-05-06 14:16:36
@@ -1,24 +1,21 @@
 #include <stdio.h>
 #include "warrior.h"
 #include "tribe.h"
+#include "battle_strategy.h"
 
-Unit* warrior_create(int id) {
+Unit* warrior_create(int id, int damage) {
     struct Unit.warrior* u = create_spec(Unit.warrior);
     u->id = id;
     u->health = 100;
-    u->@damage = 35;
+    u->@damage = damage;
     return (Unit*)u;
 }
 
 void warrior_attack<Unit* attacker, Unit* target>() {} //= 0;
 
 void unit_act<Unit.warrior* unit>(SimulationContext* context) {
-    Unit* target = get_random_alive_unit(context->enemy_tribe);
-    if(target == NULL) {
-        printf("Warrior %d didn't find enemy to attack\n", unit->id);
-        return;
-    }
-    warrior_attack<(Unit*)unit, target>();
+    BattleStrategy* strategy = tribe_get_strategy(context->own_tribe);
+    strategy_execute<strategy, (Unit*)unit>(context);
 }
 
 void warrior_attack<Unit.warrior* attacker, Unit.warrior* target>()
diff --color -ru stages/stage2/ppp/src/worker.c stages/stage3/ppp/src/worker.c
--- stages/stage2/ppp/src/worker.c	2026-04-13 15:03:31
+++ stages/stage3/ppp/src/worker.c	2026-05-06 13:47:25
@@ -1,5 +1,7 @@
 #include <stdio.h>
 #include "worker.h"
+#include "battle_strategy.h"
+#include "tribe.h"
 
 Unit* worker_create(int id) {
     struct Unit.worker* u = create_spec(Unit.worker);
@@ -10,5 +12,6 @@
 
 
 void unit_act<Unit.worker* unit>(SimulationContext* context) {
-    printf("Worker %d is working\n", unit->id);
+    BattleStrategy* strategy = tribe_get_strategy(context->own_tribe);
+    strategy_execute<strategy, (Unit*)unit>(context);
 }
```