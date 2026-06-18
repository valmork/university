import java.util.Scanner

// Модели данных
data class Symptom(
    val id: String,
    val question: String,
    val weight: Double = 1.0  // вес симптома для нечеткой логики
)

data class Diagnosis(
    val name: String,
    val probability: Double,  // 0..1
    val recommendations: List<String>,
    val possibleCauses: List<String>
)

// Пользовательский ответ
data class UserResponse(
    val symptomId: String,
    val severity: Double  // 0 = нет, 1 = слабо, 2 = средне, 3 = сильно
)

// База знаний
object KnowledgeBase {
    // Список симптомов - 13 симптомов
    val symptoms = listOf(
        Symptom("engine_lamp", "Горит ли 'Check Engine' на панели?", 1.5),
        Symptom("hard_start", "Трудно запустить двигатель?", 1.2),
        Symptom("unstable_idle", "Нестабильные обороты на холостом ходу?", 1.3),
        Symptom("power_loss", "Потеря мощности при разгоне?", 1.4),
        Symptom("smoke_black", "Черный дым из выхлопной трубы?", 1.2),
        Symptom("smoke_blue", "Синий или белый дым?", 1.3),
        Symptom("overheat", "Двигатель перегревается?", 1.5),
        Symptom("oil_leak", "Заметны ли подтеки масла?", 1.0),
        Symptom("knocking", "Стук в двигателе?", 1.6),
        Symptom("vibration", "Вибрация при движении?", 1.2),
        Symptom("brake_squeal", "Писк при торможении?", 0.8),
        Symptom("battery_drain", "Быстро садится аккумулятор?", 1.1),
        Symptom("strange_sound", "Посторонний шум при работе?", 1.4)
    )

    // Диагностические правила (условия, диагноз, вероятностный вес)
    data class Rule(
        val conditions: Map<String, Double>, // symptomId -> минимальная степень проявления
        val diagnosis: Diagnosis,
        val ruleWeight: Double = 1.0
    )
    // 8 правил
    val rules = listOf(
        Rule(
            mapOf("engine_lamp" to 1.0, "power_loss" to 1.0),
            Diagnosis(
                "Неисправность датчика кислорода или катализатора",
                0.85,
                listOf(
                    "Считайте ошибки через OBD2 сканер",
                    "Проверьте показания лямбда-зонда",
                    "Осмотрите катализатор на предмет забитости"
                ),
                listOf("Лямбда-зонд", "Катализатор", "Пропуски зажигания")
            ),
            1.3
        ),
        Rule(
            mapOf("hard_start" to 1.5, "unstable_idle" to 1.0),
            Diagnosis(
                "Проблемы с топливной системой или свечами",
                0.75,
                listOf(
                    "Проверьте свечи зажигания и катушки",
                    "Измерьте давление топлива в рампе",
                    "Проверьте форсунки на утечку"
                ),
                listOf("Свечи", "Форсунки", "Топливный насос", "Дроссельная заслонка")
            ),
            1.2
        ),
        Rule(
            mapOf("smoke_black" to 1.5, "power_loss" to 1.5),
            Diagnosis(
                "Переобогащенная топливовоздушная смесь",
                0.9,
                listOf(
                    "Проверьте датчик массового расхода воздуха (ДМРВ)",
                    "Проверьте датчик температуры охлаждающей жидкости",
                    "Проверьте форсунки на герметичность"
                ),
                listOf("ДМРВ", "Лямбда-зонд", "Форсунки", "Регулятор давления топлива")
            ),
            1.4
        ),
        Rule(
            mapOf("smoke_blue" to 1.5),
            Diagnosis(
                "Масло попадает в камеру сгорания",
                0.8,
                listOf(
                    "Проверьте маслосъемные колпачки",
                    "Проведите компрессию цилиндров",
                    "Проверьте турбокомпрессор (если есть)"
                ),
                listOf("Маслосъемные колпачки", "Поршневые кольца", "Турбина")
            ),
            1.3
        ),
        Rule(
            mapOf("overheat" to 1.5),
            Diagnosis(
                "Проблема системы охлаждения",
                0.85,
                listOf(
                    "Проверьте уровень антифриза",
                    "Проверьте термостат",
                    "Проверьте радиатор и вентилятор",
                    "Проверьте помпу"
                ),
                listOf("Термостат", "Помпа", "Радиатор", "Утечка антифриза")
            ),
            1.4
        ),
        Rule(
            mapOf("knocking" to 1.5, "power_loss" to 1.0),
            Diagnosis(
                "Детонация или механическая неисправность двигателя",
                0.95,
                listOf(
                    "Проверьте качество топлива (октановое число)",
                    "Срочно проверьте шатунно-поршневую группу",
                    "Проверьте угол опережения зажигания"
                ),
                listOf("Низкокачественное топливо", "Износ вкладышей", "Поршневые пальцы")
            ),
            1.6
        ),
        Rule(
            mapOf("vibration" to 1.2, "engine_lamp" to 0.8),
            Diagnosis(
                "Пропуски зажигания (Misfire)",
                0.7,
                listOf(
                    "Проверьте свечи, высоковольтные провода",
                    "Проверьте катушки зажигания",
                    "Проведите диагностику форсунок"
                ),
                listOf("Свечи", "Катушки", "Форсунки", "Компрессия")
            ),
            1.2
        ),
        Rule(
            mapOf("battery_drain" to 1.5, "hard_start" to 1.0),
            Diagnosis(
                "Неисправность генератора или утечка тока",
                0.8,
                listOf(
                    "Проверьте напряжение на клеммах АКБ при работе двигателя (13.5-14.5V)",
                    "Измерьте ток утечки при выключенном зажигании",
                    "Проверьте ремень генератора"
                ),
                listOf("Генератор", "Регулятор напряжения", "Паразитная утечка тока")
            ),
            1.3
        )
    )
}

// Механизм вывода
class InferenceEngine {
    fun evaluate(
        responses: List<UserResponse>,
        minProbability: Double = 0.3
    ): List<DiagnosisWithScore> {
        val symptomMap = responses.associate { it.symptomId to it.severity }

        val results = KnowledgeBase.rules.mapNotNull { rule ->
            var matchDegree = 1.0
            var ruleFired = true

            // Проверяем каждое условие правила
            for ((symptomId, requiredSeverity) in rule.conditions) {
                val actualSeverity = symptomMap[symptomId] ?: 0.0
                if (actualSeverity < requiredSeverity) {
                    ruleFired = false
                    break
                }
                // Степень соответствия (чем выше actual, тем лучше)
                val conditionMatch = minOf(1.0, actualSeverity / requiredSeverity)
                matchDegree *= conditionMatch
            }

            if (ruleFired) {
                // Учитываем вес правила и базовую вероятность диагноза
                val finalProbability = rule.diagnosis.probability * matchDegree * rule.ruleWeight
                if (finalProbability >= minProbability) {
                    DiagnosisWithScore(
                        diagnosis = rule.diagnosis,
                        probability = finalProbability.coerceIn(0.0, 1.0),
                        matchedSymptoms = rule.conditions.keys.filter { it in symptomMap },
                        rule = rule
                    )
                } else null
            } else null
        }

        return results.sortedByDescending { it.probability }
    }
}

data class DiagnosisWithScore(
    val diagnosis: Diagnosis,
    val probability: Double,
    val matchedSymptoms: List<String>,
    val rule: KnowledgeBase.Rule
)

// Интерфейс взаимодействия
class ExpertSystemUI(private val inferenceEngine: InferenceEngine) {
    private val scanner = Scanner(System.`in`)

    fun runDiagnostic() {
        println("\nДобро пожаловать в экспертную систему диагностики автомобиля!")
        println("Отвечайте на вопросы, оценивая симптом по шкале:")
        println("(можно вводить дробные значения, например 1.5)\n")
        println("0 - Нет")
        println("1 - Слабо / Иногда")
        println("2 - Средне / Часто")
        println("3 - Сильно / Постоянно")

        val responses = mutableListOf<UserResponse>()

        for (symptom in KnowledgeBase.symptoms) {
            print("${symptom.question} [0-3] : ")
            val input = scanner.nextLine().trim()
            val severity = input.toDoubleOrNull()
            if (severity != null && severity in 0.0..3.0) {
                if (severity > 0.0) {
                    responses.add(UserResponse(symptom.id, severity))
                }
            } else {
                println("Некорректный ввод. Пропускаем (будет 0).")
            }
        }

        if (responses.isEmpty()) {
            println("\nСимптомы не обнаружены. Автомобиль, вероятно, исправен.")
            return
        }

        println("\nАнализ симптомов...\n")
        val results = inferenceEngine.evaluate(responses)

        if (results.isEmpty()) {
            println("Не удалось определить неисправность с достаточной уверенностью.")
            println("Рекомендуем обратиться к профессиональному диагносту.")
        } else {
            println("Результаты диагностики (от наиболее вероятных):\n")
            for ((index, res) in results.withIndex()) {
                val percent = (res.probability * 100).toInt()
                println("${index + 1}. [Вероятность ${percent}%] ${res.diagnosis.name}")
                println("Возможные причины: ${res.diagnosis.possibleCauses.joinToString(", ")}")
                println("Рекомендации:")
                res.diagnosis.recommendations.forEach { rec ->
                    println("$rec")
                }
                println("Сработавшие симптомы: ${res.matchedSymptoms.joinToString { getSymptomName(it) }}")
            }

            println("Совет: Проверьте комбинацию наиболее вероятных диагнозов.")
        }

        askForFeedback()
    }

    private fun getSymptomName(symptomId: String): String {
        return KnowledgeBase.symptoms.find { it.id == symptomId }?.question?.take(30) ?: symptomId
    }

    private fun askForFeedback() {
        println("\nПомогла ли вам диагностика? (да/нет/частично)")
        val feedback = scanner.nextLine().trim().lowercase()
        when (feedback) {
            "да" -> println("Рады помочь! Хорошей дороги!")
            "нет" -> println("Извините. Попробуйте провести более детальную диагностику у специалиста.")
            "частично" -> println("Спасибо за честность! Система будет улучшаться.")
            else -> println("Спасибо за использование системы!")
        }
    }
}

// Точка входа
fun main() {
    val engine = InferenceEngine()
    val ui = ExpertSystemUI(engine)

    while (true) {
        ui.runDiagnostic()
        println("\nПовторить диагностику? (да/нет)")
        val answer = readlnOrNull()?.trim()?.lowercase()
        if (answer != "да") {
            println("До свидания!")
            break
        }
    }
}