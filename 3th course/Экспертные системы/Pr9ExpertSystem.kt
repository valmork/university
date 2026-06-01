data class Rule(
    val name: String,
    val condition: (Map<String, Any>) -> Boolean,
    val conclusion: String
)

class ExpertSystem {
    private val rules = mutableListOf<Rule>()

    fun addRule(rule: Rule) = rules.add(rule)

    fun evaluate(facts: Map<String, Any>): List<String> {
        val recommendations = mutableSetOf<String>()
        for (rule in rules) {
            if (rule.condition(facts)) {
                recommendations.add(rule.conclusion)
            }
        }
        return recommendations.toList()
    }
}

data class Question(
    val id: String,
    val text: String,
    val type: QuestionType,
    val options: List<Pair<String, Any>>? = null,
    val dependsOn: Map<String, Any>? = null
)

enum class QuestionType {
    BOOLEAN,
    STRING,
    SINGLE_CHOICE
}

class DialogEngine {
    private val questions = mutableListOf<Question>()
    private val answers = mutableMapOf<String, Any>()

    fun addQuestion(question: Question) = questions.add(question)

    fun runDialog(): Map<String, Any> {
        println("Экспертная система по выбору системы защиты информации. Пожалуйста, ответьте на несколько вопросов.\n")

        for (question in questions) {
            // Проверяем зависимости
            if (question.dependsOn != null) {
                var showQuestion = true
                for ((depId, requiredValue) in question.dependsOn) {
                    if (answers[depId] != requiredValue) {
                        showQuestion = false
                        break
                    }
                }
                if (!showQuestion) continue
            }

            if (answers.containsKey(question.id)) continue

            println(question.text)

            when (question.type) {
                QuestionType.BOOLEAN -> {
                    print("Введите 1 (Да) или 0 (Нет): ")
                    val input = readLine()?.trim()
                    val answer = when (input) {
                        "1", "да", "yes", "y", "д" -> true
                        else -> false
                    }
                    answers[question.id] = answer
                    println("Ответ: ${if (answer) "Да" else "Нет"}\n")
                }

                QuestionType.SINGLE_CHOICE -> {
                    question.options?.forEachIndexed { index, (display, _) ->
                        println("   ${index + 1}. $display")
                    }
                    print("Ваш выбор (1-${question.options?.size}): ")
                    val input = readLine()?.trim()
                    val index = input?.toIntOrNull()?.minus(1)
                    if (index != null && index in 0 until (question.options?.size ?: 0)) {
                        val value = question.options!![index].second
                        answers[question.id] = value
                        println("Выбрано: ${question.options!![index].first}\n")
                    } else {
                        println("Неверный ввод. Использую значение по умолчанию\n")
                        answers[question.id] = question.options?.first()?.second ?: ""
                    }
                }

                QuestionType.STRING -> {
                    print("Введите значение: ")
                    val input = readLine()?.trim() ?: ""
                    answers[question.id] = input
                    println("Принято: $input\n")
                }
            }
        }

        return answers
    }
}

fun createQuestions(): List<Question> {
    return listOf(
        Question(
            id = "need_security",
            text = "Требуется ли система защиты информации вообще?",
            type = QuestionType.BOOLEAN
        ),

        Question(
            id = "data_classification",
            text = "Каков максимальный уровень конфиденциальности данных?",
            type = QuestionType.SINGLE_CHOICE,
            options = listOf(
                "Не секретные" to "unclassified",
                "Коммерческая тайна/ДСП" to "confidential",
                "Персональные данные" to "personal_data",
                "Гостайна/Сов. секретно" to "Гостайна"
            )
        ),

        Question(
            id = "fstec_required",
            text = "Требуется ли сертификация ФСТЭК России?",
            type = QuestionType.BOOLEAN
        ),

        Question(
            id = "fsb_required",
            text = "Требуется ли сертификация ФСБ (для криптографии)?",
            type = QuestionType.BOOLEAN
        ),

        Question(
            id = "budget",
            text = "Оцените ваш бюджет на СЗИ (примерно):",
            type = QuestionType.SINGLE_CHOICE,
            options = listOf(
                "До 100 тыс. руб." to "low",
                "100 тыс. - 1 млн руб." to "medium",
                "Более 1 млн руб." to "high"
            )
        ),

        Question(
            id = "os",
            text = "Какая операционная система используется на большинстве рабочих станций?",
            type = QuestionType.SINGLE_CHOICE,
            options = listOf(
                "Windows" to "Windows",
                "Linux" to "Linux",
                "Смешанная (Windows + Linux)" to "Windows_Linux_mixed",
                "macOS" to "macOS"
            )
        ),

        Question(
            id = "threat_source",
            text = "Какой источник угроз для вас наиболее критичен?",
            type = QuestionType.SINGLE_CHOICE,
            options = listOf(
                "Внешние (хакеры, вирусы из интернета)" to "external",
                "Внутренние (сотрудники, утечки)" to "internal",
                "Оба одинаково критичны" to "both"
            )
        ),

        Question(
            id = "internet_connected",
            text = "Имеется ли подключение к интернету у защищаемых систем?",
            type = QuestionType.BOOLEAN
        ),

        Question(
            id = "is_critical_infrastructure",
            text = "Является ли объект критической информационной инфраструктурой (КИИ)?",
            type = QuestionType.BOOLEAN
        ),

        Question(
            id = "need_certification",
            text = "Требуется ли аттестация объекта информатизации (по требованиям ФСТЭК)?",
            type = QuestionType.BOOLEAN
        ),

        Question(
            id = "need_av",
            text = "Требуется ли антивирусная защита?",
            type = QuestionType.BOOLEAN
        ),

        Question(
            id = "encryption_needed",
            text = "Нужно ли шифрование данных?",
            type = QuestionType.BOOLEAN
        ),

        Question(
            id = "need_dlp",
            text = "Нужна ли защита от утечек (DLP-система)?",
            type = QuestionType.BOOLEAN
        ),

        Question(
            id = "personal_data_level",
            text = "Если есть персональные данные, какой у них уровень защищённости?",
            type = QuestionType.SINGLE_CHOICE,
            options = listOf(
                "Нет ПДн" to 0,
                "3 уровень (самый низкий)" to 3,
                "2 уровень (средний)" to 2,
                "1 уровень (высокий)" to 1
            ),
            dependsOn = mapOf("data_classification" to "personal_data")
        ),

        Question(
            id = "has_mobile_devices",
            text = "Используются ли мобильные устройства (телефоны, планшеты) для работы с данными?",
            type = QuestionType.BOOLEAN
        ),

        Question(
            id = "need_mdm",
            text = "Требуется ли управление мобильными устройствами (MDM)?",
            type = QuestionType.BOOLEAN,
            dependsOn = mapOf("has_mobile_devices" to true)
        ),

        Question(
            id = "has_sec_team",
            text = "Есть ли в штате специалист по информационной безопасности?",
            type = QuestionType.BOOLEAN
        ),

        Question(
            id = "num_pcs",
            text = "Сколько примерно компьютеров нужно защищать?",
            type = QuestionType.SINGLE_CHOICE,
            options = listOf(
                "1-10" to 5,
                "11-50" to 30,
                "51-200" to 100,
                "Более 200" to 300
            )
        )
    )
}

fun createSecurityRules(): List<Rule> {
    return listOf(
        Rule("Совершенно секретно",
            { it["data_classification"] == "Гостайна" && it["fstec_required"] == true && it["need_certification"] == true },
            "ViPNet Coordinator (ФСТЭК, сертифицирован для Гостайны)"),

        Rule("КИИ объект",
            { it["is_critical_infrastructure"] == true },
            "Kaspersky Industrial CyberSecurity (защита АСУ ТП, КИИ)"),

        Rule("Облачная защита для малого бизнеса",
            { it["threat_source"] == "external" && (it["budget"] == "low" || it["budget"] == "medium") && it["internet_connected"] == true },
            "Kaspersky Endpoint Security Cloud"),

        Rule("Криптография ФСБ",
            { it["fsb_required"] == true && it["encryption_needed"] == true },
            "КриптоПро CSP + ViPNet Coordinator (ФСБ)"),

        Rule("Защита от утечек (DLP)",
            { it["need_dlp"] == true },
            "Solar Dozor (DLP) или InfoWatch Traffic Monitor"),

        Rule("Стандартная корпоративная защита Windows",
            { it["os"] == "Windows" && (it["budget"] == "medium" || it["budget"] == "high") && it["need_av"] == true },
            "Kaspersky Endpoint Security для Windows"),

        Rule("Защищенная ОС Linux",
            { it["os"] == "Linux" && it["budget"] == "high" && it["fstec_required"] == true },
            "Astra Linux Special Edition + СЗИ от НСД (Dallas Lock или Sibel)"),

        Rule("Гибридная среда",
            { it["os"] == "Windows_Linux_mixed" && it["budget"] != "low" },
            "Kaspersky Hybrid Cloud Security"),

        Rule("Минимальный бюджет",
            { it["budget"] == "low" && it["need_av"] == true && it["fstec_required"] != true },
            "Dr.Web Desktop Security (базовая антивирусная защита)"),

        Rule("Защита мобильных устройств",
            { it["has_mobile_devices"] == true && it["need_mdm"] == true },
            "Kaspersky Mobile Security Management (MDM)"),

        Rule("Аттестация объекта информатизации",
            { it["need_certification"] == true && it["fstec_required"] == true && it["data_classification"] != "Гостайна" },
            "Dallas Lock 8.0 или Sibel (сертифицированные СЗИ от НСД)"),

        Rule("Персональные данные высокого уровня",
            { it["personal_data_level"] in listOf(1, 2) && it["fstec_required"] == true },
            "ViPNet SIES (защита ПДн до 1 уровня)"),

        Rule("Нет ИБ-специалиста",
            { it["has_sec_team"] == false && it["budget"] != "low" },
            "Kaspersky EDR (Managed Detection and Response)"),

        Rule("Сертифицированный антивирус",
            { it["need_av"] == true && it["fstec_required"] == true && it["os"] == "Windows" },
            "Kaspersky Anti-Virus 6.0 for Windows (сертификат ФСТЭК)"),

        Rule("Автономная локальная сеть",
            { it["internet_connected"] == false && it["budget"] == "low" && (it["num_pcs"] as? Int ?: 0) in 1..30 },
            "Бесплатный антивирус (Avast/AVG) + групповые политики Windows")
    )
}

fun main() {
    val expertSystem = ExpertSystem()
    val rules = createSecurityRules()
    rules.forEach { expertSystem.addRule(it) }

    val dialog = DialogEngine()
    val questions = createQuestions()
    questions.forEach { dialog.addQuestion(it) }

    val facts = dialog.runDialog()

    if (facts["need_security"] != true) {
        println("\nСистема защиты информации не требуется. До свидания!")
        return
    }

    val recommendations = expertSystem.evaluate(facts)

    println("\nРЕЗУЛЬТАТЫ АНАЛИЗА\n")
    if (recommendations.isEmpty()) {
        println("К сожалению, не удалось подобрать конкретную СЗИ. Рекомендуем: провести аудит ИБ и обратиться к сертифицированному интегратору")
    } else {
        println("На основе ваших ответов рекомендуется:\n")
        recommendations.forEachIndexed { index, rec ->
            println("${index + 1}. $rec")
        }
    }
}