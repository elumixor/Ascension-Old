import java.util.*

// User manager manages users' authorization, registration, account deletion and editing.

class User(val login: String) {
    val password = ""

    var authorized = false

    override fun toString(): String = login
}

class Account(val createdOn: Date, val user: User, val trial: Boolean)

class UserManager {
    private val users: MutableMap<String, User> = mutableMapOf()

    operator fun get(name: String): User? {
        return users[name]
    }

    fun list(): List<User> {
        return users.toList().map { e -> e.second }
    }

    fun register(login: String): Boolean {
        if (users.containsKey(login)) return false
        else users[login] = User(login)
        return true
    }

    fun delete(login: String): Boolean {
        if (!users.containsKey(login)) return false
        else users.remove(login)
        return true
    }
}
