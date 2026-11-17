Сборка из .\fleet: g++ *.cpp -o fleet.exe
Запуск: .\fleet.exe

Inventory.hpp: InventoryItem и EnergyConsumer.
Transport.hpp: Transport от InventoryItem; Bike, ElectricScooter, ElectricBike, Helicopter от Transport.
Things.hpp: Helmet и Dock от InventoryItem.
ElectricScooter, ElectricBike, Helicopter и Dock также от EnergyConsumer; virtual inheritance нет.
Inventory.cpp: << через Describe, < и == по id, == для проверки дубликатов.
novice [min_score] задаёт порог отбора, без аргумента 6. list сортирует временный список указателей.

Fleet.cpp: unique_ptr -> проверка id и техосмотр в ServiceCenter -> shared_ptr в парке.
Витрина — weak_ptr; повторное добавление того же id старый фокус не восстанавливает.

Errors.hpp: FleetError -> InspectionRejected (broken в имени транспорта), InvalidCommand (аргументы, повторный или ненайденный id).

Registry<T> в Registry.hpp хранит позиции, шаблонная SumEnergy используется в energy.

Креативная часть:
1. add helicopter id name energy, простота 3.
2. closest score выбирает транспорт с ближайшей простотой, при равенстве меньший id, без транспорта пишет no transport

ИИ для консультаций, исправления багов
