export function arraysEqual<T>(arr1: Array<T>, arr2: Array<T>) {
  if (arr1 == null) return arr2 == null;
  if (!arr2 || arr1.length !== arr2.length) return false;

  const _arr1 = arr1.slice().sort();
  const _arr2 = arr2.slice().sort();

  for (let i = 0; i < _arr1.length; i++) if (_arr1[i] !== _arr2[i]) return false;

  return true;
}

const {defineProperty, getPrototypeOf} = Object;

/**
 * Lazy initialization decorator from
 * https://stackoverflow.com/questions/42845543/in-typescript-is-there-a-syntax-for-declaring-a-field-as-lazy
 */
export function lazy(target, name, {get: initializer, enumerable, configurable, set: setter}: PropertyDescriptor = {}): any {
  const {constructor} = target;
  if (initializer === undefined) {
    throw `@lazy can't be set as a property '${name}' on ${constructor.name} class, using a getter instead!`;
  }
  if (setter) {
    throw `@lazy can't be annotated with get ${name}() existing a setter on ${constructor.name} class!`;
  }

  function set(that, value) {
    if (value === undefined) {
      value = that;
      that = this;
    }
    defineProperty(that, name, {
      enumerable: enumerable,
      configurable: configurable,
      value: value
    });
    return value;
  }

  return {
    get() {
      if (this === target) {
        return initializer;
      }
      //note:subclass.prototype.foo when foo exists in superclass nor subclass, this will be called
      if (this.constructor !== constructor && getPrototypeOf(this).constructor === constructor) {
        return initializer;
      }
      return set(this, initializer.call(this));
    },
    set
  };
}
