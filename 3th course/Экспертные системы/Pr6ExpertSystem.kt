// МОДЕЛИ ДАННЫХ
data class Component(val name: String, val price: Int, val description: String)
data class Recommendation(
    val cpu: Component, val ram: Component, val gpu: Component,
    val storage: Component, val motherboard: Component, val psu: Component,
    val cooler: Component, val explanations: List<String>
)

// ФАКТЫ ПОЛЬЗОВАТЕЛЯ
data class UserFacts(
    var purpose: String = "",
    var budget: Int = 0,
    var needMultitasking: Boolean = false,
    var needStorage: Boolean = false,
    var needVideo: Boolean = false,
    var need3D: Boolean = false,
    var needGaming: Boolean = false,
    var needProgramming: Boolean = false
)

// БАЗА ЗНАНИЙ

object KnowledgeBase {

    val cpus = mapOf(
        "budget_basic"     to Component("Intel Core i3-12100",       9_500,  "4 ядра / 8 потоков, 3.3-4.3 ГГц"),
        "budget_mid"       to Component("AMD Ryzen 5 5600",          13_000, "6 ядер / 12 потоков, 3.5-4.4 ГГц"),
        "mid_gaming"       to Component("Intel Core i5-13600K",      22_000, "14 ядер / 20 потоков, 3.5-5.1 ГГц"),
        "mid_workstation"  to Component("AMD Ryzen 7 5800X",         24_000, "8 ядер / 16 потоков, 3.8-4.7 ГГц"),
        "high_gaming"      to Component("Intel Core i7-13700K",      35_000, "16 ядер / 24 потока, 3.4-5.4 ГГц"),
        "high_workstation" to Component("AMD Ryzen 9 7900X",         45_000, "12 ядер / 24 потока, 4.7-5.6 ГГц"),
        "extreme"          to Component("AMD Ryzen 9 7950X",         65_000, "16 ядер / 32 потока, 4.5-5.7 ГГц")
    )
    val rams = mapOf(
        "8gb"  to Component("DDR4 8 GB 3200 MHz",  3_500,  "Базовый объём для офиса и учёбы"),
        "16gb" to Component("DDR4 16 GB 3600 MHz", 7_000,  "Оптимально для большинства задач"),
        "32gb" to Component("DDR5 32 GB 5600 MHz", 14_000, "Для профессиональных задач и игр"),
        "64gb" to Component("DDR5 64 GB 5600 MHz", 28_000, "Для видеомонтажа и серверов")
    )
    val gpus = mapOf(
        "integrated" to Component("Встроенная графика (iGPU)",    0,       "Для офиса без игр"),
        "budget"     to Component("NVIDIA GeForce RTX 3050",      18_000,  "Начальный уровень для игр"),
        "mid"        to Component("NVIDIA GeForce RTX 4060",      32_000,  "Оптимально для игр 1080p/1440p"),
        "high"       to Component("NVIDIA GeForce RTX 4070 Ti",   65_000,  "Высокая производительность 1440p/4K"),
        "pro"        to Component("NVIDIA RTX A4000",              90_000,  "Профессиональная для 3D и рендеринга"),
        "extreme"    to Component("NVIDIA GeForce RTX 4090",      160_000, "Флагман для 4K и тяжёлого рендеринга")
    )
    val storages = mapOf(
        "ssd_512" to Component("SSD NVMe 512 GB",      4_000,  "Система + базовые программы"),
        "ssd_1tb" to Component("SSD NVMe 1 TB",        7_000,  "Комфортный объём для большинства"),
        "ssd_2tb" to Component("SSD NVMe 2 TB",        13_000, "Для больших коллекций и проектов"),
        "ssd_hdd" to Component("SSD 1 TB + HDD 4 TB", 17_000, "Скорость + большой объём")
    )
    val motherboards = mapOf(
        "budget_intel" to Component("ASRock B660M Pro RS",      7_000,  "mATX, LGA1700, DDR4"),
        "budget_amd"   to Component("MSI B550M PRO-VDH WIFI",  7_500,  "mATX, AM4, DDR4, Wi-Fi"),
        "mid_intel"    to Component("ASUS PRIME Z790-P",        18_000, "ATX, LGA1700, DDR5"),
        "mid_amd"      to Component("MSI MAG X570S TOMAHAWK",  16_000, "ATX, AM4, DDR4"),
        "high_amd"     to Component("ASUS ROG CROSSHAIR X670E",35_000, "ATX, AM5, DDR5, Wi-Fi")
    )
    val psus = mapOf(
        "400w"  to Component("Corsair CV450 450W 80+ Bronze",    3_500,  "Для офисных ПК"),
        "650w"  to Component("Seasonic Focus GX-650 80+ Gold",   8_000,  "Для среднего уровня"),
        "850w"  to Component("be quiet! Straight Power 850W",    13_000, "Для мощных систем"),
        "1000w" to Component("Corsair HX1000 80+ Platinum",      18_000, "Для топовых конфигураций")
    )
    val coolers = mapOf(
        "stock"  to Component("Боксовый кулер",         0,     "Базовое охлаждение"),
        "budget" to Component("DeepCool AK400",          2_500, "Тихое воздушное охлаждение"),
        "mid"    to Component("Noctua NH-U12S",          5_000, "Премиум воздушное охлаждение"),
        "liquid" to Component("NZXT Kraken X63 СЖО",    9_000, "Жидкостное охлаждение 240мм")
    )
}

// БАЗА ПРАВИЛ (ТОЛЬКО ЖЕЛЕЗО)

object RuleEngine {
    fun infer(facts: UserFacts): Recommendation {
        val exp = mutableListOf<String>()

        val highLoad    = facts.needGaming || facts.needVideo || facts.need3D
        val heavyBudget = facts.budget > 100_000

        // ПРАВИЛО 1: Процессор
        val cpu = when {
            highLoad && heavyBudget -> {
                exp += "Правило 1: Высокая нагрузка + бюджет>100к -> AMD Ryzen 9 7950X"
                KnowledgeBase.cpus["extreme"]!! }
            highLoad && facts.budget in 60_000..100_000 -> {
                exp += "Правило 1: Высокая нагрузка, средний бюджет -> Intel Core i5-13600K"
                KnowledgeBase.cpus["mid_gaming"]!! }
            facts.needProgramming && facts.needMultitasking -> {
                exp += "Правило 1: Программирование + многозадачность -> AMD Ryzen 7 5800X"
                KnowledgeBase.cpus["mid_workstation"]!! }
            facts.budget < 40_000 -> {
                exp += "Правило 1: Бюджетный ПК -> Intel Core i3-12100"
                KnowledgeBase.cpus["budget_basic"]!! }
            else -> {
                exp += "Правило 1: Универсальный ПК -> AMD Ryzen 5 5600"
                KnowledgeBase.cpus["budget_mid"]!! }
        }

        // ПРАВИЛО 2: Видеокарта
        val gpu = when {
            facts.need3D && heavyBudget -> {
                exp += "Правило 2: Профессиональный 3D + бюджет>100к -> NVIDIA RTX A4000"
                KnowledgeBase.gpus["pro"]!! }
            facts.needGaming && heavyBudget -> {
                exp += "Правило 2: Топовые игры + бюджет>100к -> RTX 4090"
                KnowledgeBase.gpus["extreme"]!! }
            (facts.needGaming || facts.needVideo) && facts.budget > 60_000 -> {
                exp += "Правило 2: Игры/видео, бюджет>60к -> RTX 4070 Ti"
                KnowledgeBase.gpus["high"]!! }
            !facts.needGaming && !facts.need3D && !facts.needVideo -> {
                exp += "Правило 2: Нет графических задач -> встроенная графика"
                KnowledgeBase.gpus["integrated"]!! }
            else -> {
                exp += "Правило 2: Начальный уровень -> RTX 3050"
                KnowledgeBase.gpus["budget"]!! }
        }

        // ПРАВИЛО 3: Оперативная память
        val ram = when {
            (facts.needVideo || facts.need3D) && heavyBudget -> {
                exp += "Правило 3: Видео/3D + бюджет>100к -> 64 GB DDR5"
                KnowledgeBase.rams["64gb"]!! }
            facts.needGaming || facts.needProgramming || facts.needMultitasking -> {
                exp += "Правило 3: Игры / программирование / многозадачность -> 32 GB DDR5"
                KnowledgeBase.rams["32gb"]!! }
            facts.budget > 35_000 -> {
                exp += "Правило 3: Стандартный объем -> 16 GB DDR4"
                KnowledgeBase.rams["16gb"]!! }
            else -> {
                exp += "Правило 3: Минимальный бюджет -> 8 GB DDR4"
                KnowledgeBase.rams["8gb"]!! }
        }

        // ПРАВИЛО 4: Накопитель
        val storage = when {
            (facts.needVideo || facts.need3D) && facts.needStorage -> {
                exp += "Правило 4: Видео/3D + много данных -> SSD 1 TB + HDD 4 TB"
                KnowledgeBase.storages["ssd_hdd"]!! }
            facts.needGaming || facts.needStorage -> {
                exp += "Правило 4: Игры / много данных -> SSD NVMe 2 TB"
                KnowledgeBase.storages["ssd_2tb"]!! }
            facts.budget > 40_000 -> {
                exp += "Правило 4: Стандартный объём -> SSD NVMe 1 TB"
                KnowledgeBase.storages["ssd_1tb"]!! }
            else -> {
                exp += "Правило 4: Бюджетный вариант -> SSD NVMe 512 GB"
                KnowledgeBase.storages["ssd_512"]!! }
        }

        // ПРАВИЛО 5: Материнская плата
        val mb = when {
            cpu.name.contains("7950") || cpu.name.contains("7900") -> KnowledgeBase.motherboards["high_amd"]!!
            cpu.name.contains("i7")   || cpu.name.contains("i5")   -> KnowledgeBase.motherboards["mid_intel"]!!
            cpu.name.contains("Ryzen 7") -> KnowledgeBase.motherboards["mid_amd"]!!
            cpu.name.contains("i3")      -> KnowledgeBase.motherboards["budget_intel"]!!
            else -> KnowledgeBase.motherboards["budget_amd"]!!
        }
        exp += "Правило 5: Мат. плата подобрана под платформу CPU -> ${mb.name}"

        // ПРАВИЛО 6: Блок питания
        val psu = when {
            gpu.name.contains("4090") || gpu.name.contains("A4000") -> KnowledgeBase.psus["1000w"]!!
            gpu.name.contains("4070") -> KnowledgeBase.psus["850w"]!!
            gpu.name.contains("3050") -> KnowledgeBase.psus["650w"]!!
            else -> KnowledgeBase.psus["400w"]!!
        }
        exp += "Правило 6: БП подобран по TDP видеокарты -> ${psu.name}"

        // ПРАВИЛО 7: Охлаждение
        val cooler = when {
            cpu.name.contains("7950") || cpu.name.contains("7900") -> {
                exp += "Правило 7: Топовый CPU -> жидкостное охлаждение NZXT Kraken"
                KnowledgeBase.coolers["liquid"]!! }
            cpu.name.contains("i7") -> {
                exp += "Правило 7: Тихая работа / мощный CPU -> Noctua NH-U12S"
                KnowledgeBase.coolers["mid"]!! }
            cpu.name.contains("i3") -> {
                exp += "Правило 7: Бюджетный CPU -> боксовый кулер"
                KnowledgeBase.coolers["stock"]!! }
            else -> {
                exp += "Правило 7: Стандартный CPU -> DeepCool AK400"
                KnowledgeBase.coolers["budget"]!! }
        }

        return Recommendation(cpu, ram, gpu, storage, mb, psu, cooler, exp)
    }
}

// ДИАЛОГ (ТОЛЬКО ПО ЖЕЛЕЗУ)

object Dialog {
    private fun ask(question: String, vararg options: Pair<String,String>): String {
        println("\n")
        println("$question")
        options.forEachIndexed { i, (_, desc) -> println("${i+1}. $desc\n") }
        print("Ваш выбор (номер): ")
        while (true) {
            val idx = readLine()?.trim()?.toIntOrNull()
            if (idx != null && idx in 1..options.size) return options[idx-1].first
            print("  Введите номер от 1 до ${options.size}: ")
        }
    }
    private fun yn(q: String): Boolean {
        print("  $q (да/нет): ")
        while (true) {
            val ans = readLine()?.trim()?.lowercase() ?: ""
            if (ans == "да" || ans == "yes" || ans == "y" || ans == "1" || ans == "д") return true
            if (ans == "нет" || ans == "no" || ans == "n" || ans == "0" || ans == "н") return false
            print("  Введите 'да' или 'нет': ")
        }
    }
    private fun budget(): Int {
        print("  Введите бюджет в рублях (минимум 15 000): ")
        while (true) {
            val n = readLine()?.trim()?.replace(" ","")?.toIntOrNull()
            if (n != null && n >= 15_000) return n
            print("  Некорректная сумма, попробуйте ещё раз: ")
        }
    }

    fun collectFacts(): UserFacts {
        val f = UserFacts()
        println("ЭКСПЕРТНАЯ СИСТЕМА ПОДБОРА КОНФИГУРАЦИИ ПК\n")
        println("Ответьте на вопросы о ваших задачах, и система подберёт оптимальные комплектующие.\n")

        f.purpose = ask("Вопрос 1/7: Основная цель использования?",
            "gaming"  to "Игры",
            "work"    to "Работа / офис",
            "study"   to "Учёба",
            "design"  to "Дизайн / творчество",
            "server"  to "Программирование / IT",
            "general" to "Универсальное использование")

        println()
        println("  Вопрос 2/7: Бюджет на системный блок")
        f.budget = budget()

        println()
        f.needGaming = f.purpose == "gaming" || yn("Вопрос 3/7: Планируете играть в современные игры?")
        println()
        f.needVideo = f.purpose == "design" || yn("Вопрос 4/7: Нужен видеомонтаж или обработка видео?")
        println()
        f.need3D = yn("Вопрос 5/7: Работа с 3D-моделированием или рендерингом?")
        println()
        f.needProgramming = f.purpose == "server" || yn("Вопрос 6/7: Занимаетесь разработкой ПО / вычислениями?")
        println()
        f.needStorage = yn("Вопрос 7/7: Нужно много места для файлов (>2 ТБ)?")
        println()
        f.needMultitasking = yn("Дополнительно: Часто работаете в нескольких программах сразу?")

        return f
    }
}

// ВЫВОД

object ReportPrinter {
    private fun Int.fmt() = "%,d руб.".format(this).replace(",", " ")
    fun print(rec: Recommendation) {
        println("\nРЕКОМЕНДАЦИИ ПО КОМПЛЕКТУЮЩИМ \n")
        println("КОНФИГУРАЦИЯ СИСТЕМНОГО БЛОКА")
        fun ln(label: String, c: Component) {
            val p = if (c.price == 0) "в комплекте" else c.price.fmt()
            println("%-17s: %s".format(label, c.name))
            println("%s  [%s]".format(c.description, p))
            println("")
        }
        ln("Процессор (CPU)", rec.cpu)
        ln("Видеокарта (GPU)", rec.gpu)
        ln("Оперативная память", rec.ram)
        ln("Накопитель", rec.storage)
        ln("Мат. плата", rec.motherboard)
        ln("Блок питания", rec.psu)
        ln("Охлаждение", rec.cooler)
        println("\n")

        val hwTotal = listOf(rec.cpu,rec.ram,rec.gpu,rec.storage,rec.motherboard,rec.psu,rec.cooler).map{it.price}.sum()

        println("\n")
        println("ИТОГОВАЯ СТОИМОСТЬ ЖЕЛЕЗА: ${hwTotal.fmt()} \n")

        println("\n")
        println("ТРАССИРОВКА ПРИНЯТЫХ РЕШЕНИЙ\n")
        rec.explanations.forEachIndexed { i, e -> println("${i+1}. $e\n") }
    }
}

fun main() {
    while (true) {
        val facts = Dialog.collectFacts()
        val rec = RuleEngine.infer(facts)
        ReportPrinter.print(rec)
        println()
        print("Начать новый подбор? (да/нет): ")
        val again = readLine()?.trim()?.lowercase() ?: "нет"
        if (again != "да" && again != "yes" && again != "y" && again != "д" && again != "1") {
            println("\nСпасибо за использование системы! Удачи с новым ПК!")
            break
        }
    }
}