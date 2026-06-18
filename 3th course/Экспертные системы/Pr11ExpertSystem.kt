// Экспертная система выбора маршрута и транспорта

data class Location(val name: String, val region: String)

enum class Transport(
    val displayName: String,
    val speedKmh: Double,
    val costPerKm: Double,
    val baseCost: Double = 0.0
) {
    CAR("Автомобиль", 90.0, 8.0, 0.0),
    TRAIN("Поезд", 70.0, 2.5, 500.0),
    BUS("Автобус", 60.0, 1.8, 200.0),
    PLANE("Самолёт", 800.0, 9.0, 3000.0),
    TAXI("Такси", 80.0, 25.0, 100.0)
}

data class Route(
    val from: Location,
    val to: Location,
    val distanceKm: Double,
    val roadQuality: RoadQuality = RoadQuality.NORMAL
)

enum class RoadQuality {
    EXCELLENT, NORMAL, POOR
}

class TravelExpertSystemInteractive {

    private val routesDB = mutableMapOf<Pair<String, String>, Route>()
    private val cities = mutableListOf<Location>()

    init {
        // Инициализация базы маршрутов
        val moscow = Location("Москва", "Центр")
        val spb = Location("Санкт-Петербург", "Северо-Запад")
        val kazan = Location("Казань", "Поволжье")
        val ekb = Location("Екатеринбург", "Урал")
        val murmansk = Location("Мурманск", "Север")
        val sochi = Location("Сочи", "Юг")
        val novosibirsk = Location("Новосибирск", "Сибирь")

        cities.addAll(listOf(moscow, spb, kazan, ekb, murmansk, sochi, novosibirsk))

        addRoute(moscow, spb, 705.0, RoadQuality.EXCELLENT)
        addRoute(moscow, kazan, 820.0, RoadQuality.EXCELLENT)
        addRoute(moscow, ekb, 1800.0, RoadQuality.NORMAL)
        addRoute(moscow, sochi, 1620.0, RoadQuality.NORMAL)
        addRoute(moscow, novosibirsk, 3350.0, RoadQuality.NORMAL)
        addRoute(spb, murmansk, 1350.0, RoadQuality.POOR)
        addRoute(spb, moscow, 705.0, RoadQuality.EXCELLENT)
        addRoute(kazan, ekb, 970.0, RoadQuality.NORMAL)
        addRoute(ekb, novosibirsk, 1520.0, RoadQuality.NORMAL)
        addRoute(moscow, murmansk, 1970.0, RoadQuality.POOR)
    }

    private fun addRoute(from: Location, to: Location, distanceKm: Double, quality: RoadQuality) {
        val route = Route(from, to, distanceKm, quality)
        routesDB[Pair(from.name, to.name)] = route
        val reverseRoute = Route(to, from, distanceKm, quality)
        routesDB[Pair(to.name, from.name)] = reverseRoute
    }

    fun getAvailableCities(): List<String> = cities.map { it.name }.sorted()

    private fun getRoute(from: String, to: String): Route? {
        return routesDB[Pair(from, to)]
    }

    private fun calculateTime(distance: Double, transport: Transport, roadQuality: RoadQuality): Double {
        val qualityFactor = when (roadQuality) {
            RoadQuality.EXCELLENT -> 1.0
            RoadQuality.NORMAL -> 1.2
            RoadQuality.POOR -> 1.5
        }
        return distance / (transport.speedKmh / qualityFactor)
    }

    private fun calculateCost(distance: Double, transport: Transport, roadQuality: RoadQuality): Double {
        val qualitySurcharge = when (roadQuality) {
            RoadQuality.POOR -> 1.3
            else -> 1.0
        }
        val surcharge = if (transport == Transport.CAR && roadQuality == RoadQuality.POOR) qualitySurcharge else 1.0
        return transport.baseCost + (distance * transport.costPerKm * surcharge)
    }

    private fun calculateComfort(transport: Transport, distance: Double, roadQuality: RoadQuality): Int {
        var score = when (transport) {
            Transport.PLANE -> 9
            Transport.TRAIN -> 7
            Transport.CAR -> 6
            Transport.TAXI -> 5
            Transport.BUS -> 4
        }
        if (distance > 1000 && transport == Transport.BUS) score -= 3
        if (roadQuality == RoadQuality.POOR && transport == Transport.CAR) score -= 2
        if (transport == Transport.PLANE && distance < 500) score -= 2
        return score.coerceIn(1, 10)
    }

    // Диалоговый режим
    fun start() {
        println("Экспертная система по выбору маршрута и способа передвижения из одного населенного пункта в другой")

        try {
            // Выбор города отправления
            println("Шаг 1/5: выберите город отправления")
            println("Доступные города: ${getAvailableCities().joinToString(", ")}")
            print("Введите название города: ")
            val fromCity = readLine()?.trim() ?: ""

            if (getAvailableCities().none { it.equals(fromCity, ignoreCase = true) }) {
                println("Город '$fromCity' не найден в базе.")
                return
            }

            // Выбор города назначения
            println("\nШаг 2/5: выберите город назначения")
            print("Введите название города: ")
            val toCity = readLine()?.trim() ?: ""

            if (getAvailableCities().none { it.equals(toCity, ignoreCase = true) }) {
                println("Город '$toCity' не найден в базе.")
                return
            }

            if (fromCity.equals(toCity, ignoreCase = true)) {
                println("Город отправления и назначения не могут совпадать.")
                return
            }

            // Проверка наличия маршрута
            val route = getRoute(fromCity, toCity)
            if (route == null) {
                println("Прямой маршрут между '$fromCity' и '$toCity' не найден.")
                return
            }

            // Бюджет
            println("\nШаг 3/5: укажите максимальный бюджет (в рублях)")
            println("(Для пропуска введите 0)")
            print("Ваш бюджет: ")
            val budgetInput = readLine()?.trim() ?: "0"
            val maxBudget = budgetInput.toDoubleOrNull()?.takeIf { it > 0 }

            // Время в пути
            println("\nШаг 4/5: укажите максимальное время в пути (в часах). Для пропуска введите 0")
            print("Максимальное время: ")
            val timeInput = readLine()?.trim() ?: "0"
            val maxTime = timeInput.toDoubleOrNull()?.takeIf { it > 0 }

            // Приоритеты
            println("\nШаг 5/5: ваши приоритеты")
            println("Есть ли у вас личный автомобиль? (да/нет)")
            print("Ответ: ")
            val hasCar = readLine()?.trim()?.equals("да", ignoreCase = true) == true

            println("\nУ вас тяжёлый багаж? (да/нет)")
            print("Ответ: ")
            val heavyLuggage = readLine()?.trim()?.equals("да", ignoreCase = true) == true

            println("\nЧто для вас важнее?")
            println("1 - Минимальная стоимость")
            println("2 - Минимальное время в пути")
            println("3 - Максимальный комфорт")
            println("4 - Сбалансированный вариант")
            print("Выберите (1-4): ")
            val priority = readLine()?.trim()?.toIntOrNull()?.takeIf { it in 1..4 } ?: 4

            // Обработка приоритетов
            val preferComfort = priority == 3
            val preferSpeed = priority == 2
            val preferLowCost = priority == 1

            // Анализ и рекомендация
            analyzeAndRecommend(
                route = route,
                maxBudget = maxBudget,
                maxTime = maxTime,
                hasCar = hasCar,
                heavyLuggage = heavyLuggage,
                preferComfort = preferComfort,
                preferSpeed = preferSpeed,
                preferLowCost = preferLowCost
            )

        } catch (e: Exception) {
            println("\nОшибка ввода: ${e.message}")
            println("Пожалуйста, перезапустите программу и введите корректные данные.")
        }
    }

    private fun analyzeAndRecommend(
        route: Route,
        maxBudget: Double?,
        maxTime: Double?,
        hasCar: Boolean,
        heavyLuggage: Boolean,
        preferComfort: Boolean,
        preferSpeed: Boolean,
        preferLowCost: Boolean
    ) {
        println("\nАнализ вариантов поездки...")
        println("Маршрут: ${route.from.name} → ${route.to.name}")
        println("Расстояние: ${String.format("%.1f", route.distanceKm)} км")
        println("Качество дорог: ${when(route.roadQuality) {
            RoadQuality.EXCELLENT -> "Отличное"
            RoadQuality.NORMAL -> "Нормальное"
            RoadQuality.POOR -> "Плохое"
        }}")
        if (maxBudget != null) println("Бюджет: до $maxBudget руб.")
        if (maxTime != null) println("Время: до $maxTime ч")
        println()

        // Генерация всех вариантов
        val allOptions = Transport.values().map { transport ->
            val time = calculateTime(route.distanceKm, transport, route.roadQuality)
            val cost = calculateCost(route.distanceKm, transport, route.roadQuality)
            val comfort = calculateComfort(transport, route.distanceKm, route.roadQuality)

            TravelOption(
                transport = transport,
                route = route,
                cost = cost,
                timeHours = time,
                comfortScore = comfort
            )
        }

        // Применение правил экспертной системы
        var options = allOptions

        // Правило 1: бюджет
        if (maxBudget != null) {
            options = options.filter { it.cost <= maxBudget }
        }

        // Правило 2: время
        if (maxTime != null) {
            options = options.filter { it.timeHours <= maxTime }
        }

        // Правило 3: наличие авто
        if (hasCar) {
            // Не фильтруем, но добавляем бонус к авто
        }

        // Правило 4: тяжёлый багаж
        if (heavyLuggage) {
            options = options.filter { it.transport != Transport.PLANE }
            if (options.isEmpty()) options = allOptions.filter { it.transport != Transport.PLANE }
        }

        // Правило 5: дальние расстояния
        if (route.distanceKm > 1500) {
            // Самолёт получает приоритет
        }

        if (options.isEmpty()) {
            println("К сожалению, нет вариантов, удовлетворяющих всем вашим условиям.")
            println("Попробуйте увеличить бюджет или время в пути.")
            return
        }

        // Сортировка по приоритету
        val sortedOptions = when {
            preferLowCost -> options.sortedBy { it.cost }
            preferSpeed -> options.sortedBy { it.timeHours }
            preferComfort -> options.sortedByDescending { it.comfortScore }
            else -> options.sortedWith(compareBy({ it.cost }, { it.timeHours }))
        }

        // Вывод результатов
        println("Рекомендация экспертной системы:\n")

        val best = sortedOptions.first()

        // Вывод лучшего варианта
        println("Лучший вариант:")
        println("Транспорт: ${best.transport.displayName}")
        println("Стоимость: ${String.format("%.2f", best.cost)} руб.")
        println("Время в пути: ${String.format("%.1f", best.timeHours)} ч (${String.format("%.0f", best.timeHours * 60)} мин)")
        println("Комфорт: ${"★".repeat(best.comfortScore)}${"☆".repeat(10 - best.comfortScore)} (${best.comfortScore}/10)")

        // Обоснование
        println("\nОбоснование выбора")
        if (preferLowCost && best.cost == sortedOptions.minByOrNull { it.cost }?.cost) {
            println("Выбран самый дешёвый вариант")
        }
        if (preferSpeed && best.timeHours == sortedOptions.minByOrNull { it.timeHours }?.timeHours) {
            println("Выбран самый быстрый вариант")
        }
        if (preferComfort && best.comfortScore == sortedOptions.maxByOrNull { it.comfortScore }?.comfortScore) {
            println("Выбран самый комфортный вариант")
        }
        if (maxBudget != null && best.cost <= maxBudget) {
            println("Укладывается в бюджет (${String.format("%.0f", maxBudget)} руб.)")
        }
        if (maxTime != null && best.timeHours <= maxTime) {
            println("Укладывается в отведённое время")
        }
        if (hasCar && best.transport == Transport.CAR) {
            println("Использование личного автомобиля")
        }
        if (heavyLuggage && best.transport != Transport.PLANE) {
            println("Учтён тяжёлый багаж (самолёт исключён)")
        }
        if (best.transport == Transport.PLANE && route.distanceKm > 1500) {
            println("Для дальних расстояний самолёт оптимален")
        }

        // Альтернативы
        if (sortedOptions.size > 1) {
            println("\nАльтернативные варианты")
            sortedOptions.drop(1).take(3).forEachIndexed { index, opt ->
                println("   ${index + 1}. ${opt.transport.displayName}: ${String.format("%.0f", opt.cost)} руб., " +
                        "${String.format("%.1f", opt.timeHours)} ч, комфорт ${opt.comfortScore}/10")
            }
        }

        // Дополнительные советы
        println("\nСовет эксперта:")
        when {
            best.transport == Transport.PLANE -> {
                println("Билеты дешевле при покупке за 2-3 недели")
                println("Ручная кладь до 10 кг обычно бесплатна")
            }
            best.transport == Transport.TRAIN -> {
                println("Плацкарт дешевле купе на 30-40%")
                println("Покупайте билеты на сайте РЖД за 45-90 дней")
            }
            best.transport == Transport.BUS -> {
                println("Ночные рейсы дешевле и экономят время")
                println("Региональные перевозчики часто дешевле федеральных")
            }
            best.transport == Transport.CAR && !hasCar -> {
                println("Рассмотрите каршеринг для коротких поездок")
                println("Попутчики (BlaBlaCar) снизят расходы в 2-3 раза")
            }
            best.transport == Transport.TAXI -> {
                println("Межгородское такси можно заказать в приложениях")
                println("Договаривайтесь о фиксированной цене заранее")
            }
        }

        println("Спасибо за использование экспертной системы!")
    }
}

data class TravelOption(
    val transport: Transport,
    val route: Route,
    val cost: Double,
    val timeHours: Double,
    val comfortScore: Int
)

// Расширение для красивого вывода
operator fun String.times(n: Int): String = this.repeat(n)

// Точка входа
fun main() {
    val expertSystem = TravelExpertSystemInteractive()
    expertSystem.start()
}