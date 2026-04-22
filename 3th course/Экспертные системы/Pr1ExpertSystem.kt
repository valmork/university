import javax.swing.*
import javax.swing.tree.DefaultMutableTreeNode
import javax.swing.tree.DefaultTreeModel

// Модель правил и дерева
data class ProductionRule(
    val name: String,
    val pattern: String,
    val replacement: String
)

// Узел дерева сортировки (разделяем value и label!)
data class TreeNode<T>(
    val value: T,
    val label: String = value.toString(),
    val children: MutableList<TreeNode<T>> = mutableListOf()
) {
    fun addChild(child: TreeNode<T>) {
        children.add(child)
    }
}

// Механизм применения продукционных правил
class ProductionSorter(
    private val rules: List<ProductionRule>
) {
    fun sortString(initial: String): TreeNode<String> {
        val root = TreeNode(initial)
        buildTreeAll(root, mutableSetOf())
        return root
    }

    // Полное дерево всех возможных применений
    private fun buildTreeAll(node: TreeNode<String>, visited: MutableSet<String>) {
        val current = node.value
        if (current in visited) return
        visited.add(current)

        var anyApplied = false

        for (rule in rules) {
            var idx = current.indexOf(rule.pattern)

            while (idx >= 0) {
                val next = StringBuilder(current).apply {
                    replace(idx, idx + rule.pattern.length, rule.replacement)
                }.toString()

                val child = TreeNode(
                    value = next,
                    label = "${rule.name}: $next"
                )

                node.addChild(child)
                buildTreeAll(child, visited)

                anyApplied = true
                idx = current.indexOf(rule.pattern, idx + 1)
            }
        }
    }
}

// Swing-интерфейс
class ProductionSortFrame: JFrame("Production Rules Sort") {

    private val inputField = JTextField(20)

    private val rulesModel = DefaultListModel<ProductionRule>()
    private val rulesList = JList(rulesModel)

    private val treeRoot = DefaultMutableTreeNode("Result")
    private val treeModel = DefaultTreeModel(treeRoot)
    private val tree = JTree(treeModel)

    init {
        defaultCloseOperation = EXIT_ON_CLOSE
        layout = BoxLayout(contentPane, BoxLayout.Y_AXIS)

        val inputPanel = JPanel().apply {
            add(JLabel("Исходная строка:"))
            add(inputField)
        }

        val rulesPanel = JPanel().apply {
            layout = BoxLayout(this, BoxLayout.Y_AXIS)
            add(JLabel("Продукционные правила:"))
            add(JScrollPane(rulesList))

            val btnAdd = JButton("Добавить правило")
            val btnRemove = JButton("Удалить правило")

            btnAdd.addActionListener {
                val name = JOptionPane.showInputDialog(this, "Имя правила:")
                val pat = JOptionPane.showInputDialog(this, "Шаблон (pattern):")
                val rep = JOptionPane.showInputDialog(this, "Замена (replacement):")
                if (!name.isNullOrBlank() && !pat.isNullOrBlank() && rep != null) {
                    rulesModel.addElement(ProductionRule(name, pat, rep))
                }
            }

            btnRemove.addActionListener {
                val idx = rulesList.selectedIndex
                if (idx >= 0) rulesModel.remove(idx)
            }

            val buttons = JPanel()
            buttons.add(btnAdd)
            buttons.add(btnRemove)
            add(buttons)
        }

        val btnSort = JButton("Сортировать").apply {
            addActionListener { doSort() }
        }

        val treePanel = JPanel().apply {
            layout = BoxLayout(this, BoxLayout.Y_AXIS)
            add(JLabel("Дерево сортировки:"))
            add(JScrollPane(tree))
        }

        add(inputPanel)
        add(rulesPanel)
        add(btnSort)
        add(treePanel)

        // Базовые правила сортировки
        rulesModel.addElement(ProductionRule("swap_0_to_1", "0", "1"))
        rulesModel.addElement(ProductionRule("swap_1_to_2", "1", "2"))
        rulesModel.addElement(ProductionRule("swap_2_to_3", "2", "3"))

        pack()
        setLocationRelativeTo(null)
        isVisible = true
    }

    private fun doSort() {
        val text = inputField.text ?: ""
        if (text.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Введите исходную строку.")
            return
        }

        val rules = (0 until rulesModel.size()).map { rulesModel.getElementAt(it) }
        if (rules.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Добавьте хотя бы одно правило.")
            return
        }

        val sorter = ProductionSorter(rules)
        val rootNode = sorter.sortString(text)

        val newRoot = DefaultMutableTreeNode(rootNode.label)
        buildSwingTree(rootNode, newRoot)

        treeModel.setRoot(newRoot)
        treeModel.reload()

        for (i in 0 until tree.rowCount) {
            tree.expandRow(i)
        }
    }

    private fun buildSwingTree(src: TreeNode<String>, dst: DefaultMutableTreeNode) {
        for (child in src.children) {
            val childNode = DefaultMutableTreeNode(child.label)
            dst.add(childNode)
            buildSwingTree(child, childNode)
        }
    }
}

// Точка входа
fun main() {
    SwingUtilities.invokeLater { ProductionSortFrame() }
}
