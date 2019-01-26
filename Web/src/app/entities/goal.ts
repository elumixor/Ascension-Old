import {arraysEqual} from "../util/util";
import {Point} from "./point";

export class Goal {
  //region Fields
  name: string = "";
  description: string = "";
  picture: string = "";

  private _completion: number = 0;

  subGoals: Goal[] = [];
  superGoals: Goal[] = [];

  /**
   * Position in base coordinates
   */
  position: Point = new Point(0, 0);

  /**
   * History of edits
   */
  edits: Date[] = [];

  /**
   * Check if the goal is empty
   * @return {boolean}
   */
  get isEmpty(): boolean {
    return this.equals(new Goal());
  }

  /**
   * If the goal has no sub-goals, it is considered to be a simple task
   */
  get isTask(): boolean {
    return this.subGoals.length === 0;
  }

  /**
   * Goal completion rate. 0 means just started. 1 means completed.
   */
  get completion(): number {
    return this._completion;
  }

  //endregion

  constructor(name: string = "", description: string = "") {
    this.name = name;
    this.description = description;
  }

  //region Private methods
  /**
   * Updates goal completion based on the current completion of its sub-goals
   * If completion has changed, than it also updates its super-goals' progress
   */
  private update(): void {
    let completion = 0;
    this.subGoals.forEach(value => completion += value._completion);
    const oldCompletion = this._completion;
    this._completion = completion / this.subGoals.length;
    if (oldCompletion != this._completion)
      this.superGoals.forEach(g => g.update);
  }

  //endregion

  /**
   * Completes the goal if it is a task. Otherwise throws an error
   * Updates completion on related (super) goals
   */
  complete(): void {
    if (this.isTask) {
      this._completion = 1;
      this.superGoals.forEach(g => g.update());
    }
    throw new Error(`Goal '${this.name}' is not a task! Total sub-goals: ${this.subGoals.length}`);
  }

  /**
   * Create a deep copy of a goal
   */
  copy(): Goal {
    const goal = new Goal();

    goal.name = this.name;
    goal.description = this.description;
    goal.picture = this.picture;
    goal._completion = this._completion;

    this.subGoals.forEach(value => goal.subGoals.push(value));
    this.superGoals.forEach(value => goal.superGoals.push(value));
    this.edits.forEach(value => goal.edits.push(value));

    return goal;
  }

  /**
   * Update a goal with new one (assignment)
   * @param goal
   */
  assign(goal: Goal): void {
    this.name = goal.name;
    this.description = goal.description;
    this.picture = goal.picture;
    this._completion = goal._completion;

    this.subGoals.forEach(value => goal.subGoals.push(value));
    this.superGoals.forEach(value => goal.superGoals.push(value));
    this.edits.forEach(value => goal.edits.push(value));
  }

  /**
   * Checks if goals are equal. Name, description, picture are compared,
   * as well as relation to other goals (sub-/super-goals). Edits are omitted.
   * @return {boolean}
   * @param that Goal to compare against
   */
  equals(that: Goal): boolean {
    return this.name === that.name
      && this.description === that.description
      && this.picture === that.picture
      && arraysEqual(this.superGoals, that.superGoals)
      && arraysEqual(this.subGoals, that.subGoals);
  }

  /**
   * Deletes this goal from it's sub-goals and super-goals
   */
  delete(): void {
    this.superGoals.forEach(g => g.subGoals.splice(g.subGoals.indexOf(this), 1));
    this.subGoals.forEach(g => g.superGoals.splice(g.superGoals.indexOf(this), 1));
  }
}
