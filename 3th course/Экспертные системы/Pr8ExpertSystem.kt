package es

// Модель данных

enum class Temperament(val ruName: String, val description: String) {
    SANGUINE(
        "Сангвиник",
        "Живой, активный, общительный тип. Быстро адаптируется к переменам, оптимистичен, " +
                "легко заводит друзей. Эмоции яркие, но недолгие. Высокая работоспособность при разнообразии задач."
    ),
    CHOLERIC(
        "Холерик",
        "Энергичный, вспыльчивый, целеустремлённый тип. Сильная нервная система, " +
                "склонен к лидерству. Может быть агрессивным при стрессе. Быстро принимает решения."
    ),
    MELANCHOLIC(
        "Меланхолик",
        "Чувствительный, вдумчивый, творческий тип. Глубоко переживает эмоции, " +
                "склонен к анализу. Высокая тревожность, но также высокая эмпатия и внимание к деталям."
    ),
    PHLEGMATIC(
        "Флегматик",
        "Спокойный, уравновешенный, методичный тип. Медленно включается, " +
                "но очень надёжен и вынослив. Трудно выбить из колеи, предпочитает стабильность."
    ),
    MIXED(
        "Смешанный тип",
        "Черты нескольких темпераментов выражены примерно одинаково. " +
                "Гибкость поведения в зависимости от ситуации."
    )
}

// Признаки (факты о человеке)
data class Trait(val name: String, val value: Boolean)

// Правило:
data class Rule(
    val id: Int,
    val description: String,
    val conditions: List<String>, // имена признаков, которые должны быть TRUE
    val negations: List<String> = emptyList(), // имена признаков, которые должны быть FALSE
    val conclusion: Temperament,
    val weight: Double // вес правила
)

// Результат вывода
data class InferenceResult(
    val scores: Map<Temperament, Double>,
    val firedRules: List<Rule>,
    val dominant: Temperament
)

// Вопросник
data class Question(
    val id: String,
    val text: String,
    val positive: String = "Да",
    val negative: String = "Нет"
)

val QUESTIONS = listOf(
    Question("high_activity",       "Вы часто ощущаете высокий уровень энергии и активности?"),
    Question("sociable",            "Вам легко знакомиться с новыми людьми и заводить друзей?"),
    Question("quick_reaction",      "Вы обычно реагируете на события быстро, не задумываясь надолго?"),
    Question("optimistic",          "Вы, как правило, настроены оптимистично и видите светлую сторону ситуации?"),
    Question("easily_bored",        "Вам быстро надоедает однообразная работа или рутина?"),
    Question("impulsive",           "Вы склонны действовать импульсивно, не планируя заранее?"),
    Question("hot_tempered",        "Вы легко раздражаетесь и можете вспылить из-за мелочей?"),
    Question("leader",              "Вы предпочитаете занимать лидирующую позицию в группе?"),
    Question("persistent",          "Вы упорно добиваетесь своей цели, даже встречая сопротивление?"),
    Question("aggressive_stress",   "В стрессовой ситуации вы склонны к агрессивной реакции?"),
    Question("sensitive",           "Вы легко расстраиваетесь от критики или неудач?"),
    Question("anxious",             "Вы часто беспокоитесь о будущем или возможных проблемах?"),
    Question("deep_feelings",       "Ваши переживания обычно глубокие и долгие?"),
    Question("creative",            "Вы склонны к творческому мышлению и нестандартным решениям?"),
    Question("detail_oriented",     "Вы уделяете большое внимание деталям и точности?"),
    Question("calm",                "Вы, как правило, сохраняете спокойствие в напряжённых ситуациях?"),
    Question("slow_to_start",       "Вам требуется время, чтобы «включиться» в новое дело?"),
    Question("stable",              "Вы цените стабильность и предсказуемость больше, чем перемены?"),
    Question("methodical",          "Вы предпочитаете делать всё по плану, шаг за шагом?"),
    Question("enduring",            "Вы способны долго заниматься одним делом без усталости?")
)

// База правил (24 правила)
val RULES = listOf(

    // САНГВИНИК
    Rule(
        id = 1,
        description = "Высокая активность + общительность → Сангвиник",
        conditions = listOf("high_activity", "sociable"),
        conclusion = Temperament.SANGUINE,
        weight = 0.8
    ),
    Rule(
        id = 2,
        description = "Оптимизм + лёгкая скука от рутины → Сангвиник",
        conditions = listOf("optimistic", "easily_bored"),
        conclusion = Temperament.SANGUINE,
        weight = 0.75
    ),
    Rule(
        id = 3,
        description = "Быстрая реакция + общительность + оптимизм → Сангвиник (сильное)",
        conditions = listOf("quick_reaction", "sociable", "optimistic"),
        conclusion = Temperament.SANGUINE,
        weight = 0.95
    ),
    Rule(
        id = 4,
        description = "Импульсивность + общительность − горячность → Сангвиник",
        conditions = listOf("impulsive", "sociable"),
        negations = listOf("hot_tempered"),
        conclusion = Temperament.SANGUINE,
        weight = 0.7
    ),
    Rule(
        id = 5,
        description = "Высокая активность + лёгкая скука − тревожность → Сангвиник",
        conditions = listOf("high_activity", "easily_bored"),
        negations = listOf("anxious"),
        conclusion = Temperament.SANGUINE,
        weight = 0.72
    ),
    Rule(
        id = 6,
        description = "Оптимизм + быстрая реакция − чувствительность → Сангвиник",
        conditions = listOf("optimistic", "quick_reaction"),
        negations = listOf("sensitive"),
        conclusion = Temperament.SANGUINE,
        weight = 0.78
    ),

    // ХОЛЕРИК
    Rule(
        id = 7,
        description = "Высокая активность + вспыльчивость → Холерик",
        conditions = listOf("high_activity", "hot_tempered"),
        conclusion = Temperament.CHOLERIC,
        weight = 0.85
    ),
    Rule(
        id = 8,
        description = "Лидерство + настойчивость + импульсивность → Холерик (сильное)",
        conditions = listOf("leader", "persistent", "impulsive"),
        conclusion = Temperament.CHOLERIC,
        weight = 0.95
    ),
    Rule(
        id = 9,
        description = "Агрессия при стрессе + быстрая реакция → Холерик",
        conditions = listOf("aggressive_stress", "quick_reaction"),
        conclusion = Temperament.CHOLERIC,
        weight = 0.88
    ),
    Rule(
        id = 10,
        description = "Настойчивость + вспыльчивость − спокойствие → Холерик",
        conditions = listOf("persistent", "hot_tempered"),
        negations = listOf("calm"),
        conclusion = Temperament.CHOLERIC,
        weight = 0.82
    ),
    Rule(
        id = 11,
        description = "Лидерство + высокая активность − методичность → Холерик",
        conditions = listOf("leader", "high_activity"),
        negations = listOf("methodical"),
        conclusion = Temperament.CHOLERIC,
        weight = 0.75
    ),
    Rule(
        id = 12,
        description = "Агрессия при стрессе + импульсивность + лидерство → Холерик (сильное)",
        conditions = listOf("aggressive_stress", "impulsive", "leader"),
        conclusion = Temperament.CHOLERIC,
        weight = 0.97
    ),

    // МЕЛАНХОЛИК
    Rule(
        id = 13,
        description = "Чувствительность + тревожность → Меланхолик",
        conditions = listOf("sensitive", "anxious"),
        conclusion = Temperament.MELANCHOLIC,
        weight = 0.85
    ),
    Rule(
        id = 14,
        description = "Глубокие чувства + внимание к деталям + творчество → Меланхолик (сильное)",
        conditions = listOf("deep_feelings", "detail_oriented", "creative"),
        conclusion = Temperament.MELANCHOLIC,
        weight = 0.95
    ),
    Rule(
        id = 15,
        description = "Тревожность + глубокие чувства − активность → Меланхолик",
        conditions = listOf("anxious", "deep_feelings"),
        negations = listOf("high_activity"),
        conclusion = Temperament.MELANCHOLIC,
        weight = 0.88
    ),
    Rule(
        id = 16,
        description = "Чувствительность + творчество − общительность → Меланхолик",
        conditions = listOf("sensitive", "creative"),
        negations = listOf("sociable"),
        conclusion = Temperament.MELANCHOLIC,
        weight = 0.80
    ),
    Rule(
        id = 17,
        description = "Внимание к деталям + тревожность − импульсивность → Меланхолик",
        conditions = listOf("detail_oriented", "anxious"),
        negations = listOf("impulsive"),
        conclusion = Temperament.MELANCHOLIC,
        weight = 0.78
    ),
    Rule(
        id = 18,
        description = "Глубокие чувства + чувствительность − оптимизм → Меланхолик",
        conditions = listOf("deep_feelings", "sensitive"),
        negations = listOf("optimistic"),
        conclusion = Temperament.MELANCHOLIC,
        weight = 0.82
    ),

    // ФЛЕГМАТИК
    Rule(
        id = 19,
        description = "Спокойствие + стабильность → Флегматик",
        conditions = listOf("calm", "stable"),
        conclusion = Temperament.PHLEGMATIC,
        weight = 0.85
    ),
    Rule(
        id = 20,
        description = "Методичность + выносливость + медленный старт → Флегматик (сильное)",
        conditions = listOf("methodical", "enduring", "slow_to_start"),
        conclusion = Temperament.PHLEGMATIC,
        weight = 0.95
    ),
    Rule(
        id = 21,
        description = "Спокойствие + методичность − вспыльчивость → Флегматик",
        conditions = listOf("calm", "methodical"),
        negations = listOf("hot_tempered"),
        conclusion = Temperament.PHLEGMATIC,
        weight = 0.85
    ),
    Rule(
        id = 22,
        description = "Стабильность + медленный старт − активность → Флегматик",
        conditions = listOf("stable", "slow_to_start"),
        negations = listOf("high_activity"),
        conclusion = Temperament.PHLEGMATIC,
        weight = 0.82
    ),
    Rule(
        id = 23,
        description = "Выносливость + спокойствие − импульсивность → Флегматик",
        conditions = listOf("enduring", "calm"),
        negations = listOf("impulsive"),
        conclusion = Temperament.PHLEGMATIC,
        weight = 0.80
    ),
    Rule(
        id = 24,
        description = "Методичность + стабильность + выносливость − тревожность → Флегматик (сильное)",
        conditions = listOf("methodical", "stable", "enduring"),
        negations = listOf("anxious"),
        conclusion = Temperament.PHLEGMATIC,
        weight = 0.97
    )
)

// Механизм вывода (прямой цепочкой)
class InferenceEngine {

    /**
    Выполняет вывод на основе набора фактов.
    Применяет все сработавшие правила и суммирует веса по каждому темпераменту.
     **/

    fun infer(facts: Map<String, Boolean>): InferenceResult {
        val scores = mutableMapOf(
            Temperament.SANGUINE    to 0.0,
            Temperament.CHOLERIC    to 0.0,
            Temperament.MELANCHOLIC to 0.0,
            Temperament.PHLEGMATIC  to 0.0
        )
        val fired = mutableListOf<Rule>()

        for (rule in RULES) {
            val conditionsMet = rule.conditions.all { facts[it] == true }
            val negationsMet  = rule.negations.all  { facts[it] != true }

            if (conditionsMet && negationsMet) {
                fired.add(rule)
                scores[rule.conclusion] = (scores[rule.conclusion] ?: 0.0) + rule.weight
            }
        }

        // Нормализуем
        val total = scores.values.sum().takeIf { it > 0.0 } ?: 1.0
        val normalized = scores.mapValues { (_, v) -> v / total * 100.0 }

        // Определяем доминирующий тип
        val dominant = determineDominant(normalized)

        return InferenceResult(normalized, fired, dominant)
    }

    private fun determineDominant(scores: Map<Temperament, Double>): Temperament {
        val sorted = scores.entries.sortedByDescending { it.value }
        val first  = sorted[0]
        val second = sorted[1]

        // Если разница < 15% — смешанный тип
        return if (first.value - second.value < 15.0) Temperament.MIXED
        else first.key
    }
}

// Консольный интерфейс
class TemperamentApp {
    private val engine = InferenceEngine()

    fun run() {
        printHeader()
        val facts = askQuestions()
        val result = engine.infer(facts)
        printResult(result)
    }

    private fun printHeader() {
        println("ЭКСПЕРТНАЯ СИСТЕМА ОПРЕДЕЛЕНИЯ ТЕМПЕРАМЕНТА")
        println("Ответьте на ${QUESTIONS.size} вопросов: введите '1' (Да) или '0' (Нет)")
    }

    private fun askQuestions(): Map<String, Boolean> {
        val facts = mutableMapOf<String, Boolean>()
        QUESTIONS.forEachIndexed { idx, q ->
            var answer: Boolean? = null
            while (answer == null) {
                val num = (idx + 1).toString().padStart(2)
                print("  $num. ${q.text}\n      [1-Да / 0-Нет]: ")
                answer = when (readLine()?.trim()) {
                    "1", "да", "y", "yes" -> true
                    "0", "нет", "n", "no" -> false
                    else -> { println("Введите 1 или 0"); null }
                }
            }
            facts[q.id] = answer
        }
        return facts
    }

    private fun printResult(result: InferenceResult) {
        println("\nРЕЗУЛЬТАТЫ АНАЛИЗА")

        // Шкалы темпераментов
        val displayOrder = listOf(
            Temperament.SANGUINE, Temperament.CHOLERIC,
            Temperament.MELANCHOLIC, Temperament.PHLEGMATIC
        )
        displayOrder.forEach { t ->
            val pct = result.scores[t] ?: 0.0
            val bar = buildBar(pct)
            println("${t.ruName.padEnd(14)} $bar ${"%5.1f".format(pct)}%")
        }

        println("\nСработало правил: ${result.firedRules.size} из ${RULES.size}\n")

        val dom = result.dominant
        println("Доминирующий тип: ${dom.ruName.uppercase()}")
        println(wordWrap(dom.description, 56, ""))

        if (result.firedRules.isNotEmpty()) {
            println("\nСработавшие правила:")
            result.firedRules.forEach { r ->
                println("Правило ${r.id}: ${r.description}  [вес=${r.weight}]")
            }
        }
    }

    private fun buildBar(pct: Double, width: Int = 20): Int {
        return (pct / 100.0 * width).toInt()
    }

    private fun wordWrap(text: String, width: Int, indent: String): String {
        val words = text.split(" ")
        val sb = StringBuilder()
        var line = indent
        for (word in words) {
            if (line.length + word.length + 1 > width + indent.length) {
                sb.append(line).append("\n")
                line = "$indent$word"
            } else {
                line += if (line == indent) word else " $word"
            }
        }
        sb.append(line)
        return sb.toString()
    }
}

fun main() {
    TemperamentApp().run()
}