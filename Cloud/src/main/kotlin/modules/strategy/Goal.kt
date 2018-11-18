package modules.strategy

import modules.common.Trackable

open class Task(val name: String, val description: String) : Trackable() {
    var assignedTo: Goal? = null

    fun assignTo(goal: Goal) {
        goal.addSubGoal(this)
    }

    private var _isCompleted = false

    open fun complete() {
        _isCompleted = true
    }

    open fun isCompleted(): Boolean {
        return _isCompleted
    }
}

/**
 * Goal can have sub goals
 */
open class Goal(name: String, description: String) : Task(name, description) {
    private val subGoals = mutableSetOf<Task>()
    private val superGoals = mutableSetOf<Goal>()
    private var completion = 0f

    private fun breakDown(): Array<Task> {
        val tasks = mutableSetOf<Task>()

        fun iterate(goal: Goal) {
            for (g in goal.subGoals) {
                when (g) {
                    is Goal -> iterate(g)
                    else -> tasks.add(g)
                }
            }
        }

        iterate(this)
        return tasks.toTypedArray()
    }

    override fun isCompleted(): Boolean {
        return completion == 1f
    }

    fun addSubGoal(task: Task) {
        subGoals.add(task)
    }

}
