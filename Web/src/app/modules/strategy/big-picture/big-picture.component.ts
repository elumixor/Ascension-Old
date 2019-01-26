import {Component, OnInit, HostListener} from "@angular/core";
import {Goal} from "../../../entities/goal";
import {StrategyModule} from "../strategy.module";
import {BigPictureModule} from "./big-picture.module";

@Component({
  selector: "app-big-picture",
  templateUrl: "./big-picture.component.html",
  styleUrls: ["./big-picture.component.scss"]
})
export class BigPictureComponent {
  /**
   * Determine if in edit mode
   */
  get editing(): boolean { return this.editedGoal != null; }

  /**
   * Determine if should show creation hint (no goals and not in edit mode)
   */
  get showCreationHint(): boolean { return this.module.goals.length === 0 && !this.editedGoal; }

  editedGoal: Goal;

  constructor(public strategy: StrategyModule, public module: BigPictureModule) {}

  /**
   * Keys event listener
   */
  @HostListener("document:keydown", ["$event"])
  showSearch(event: KeyboardEvent) {
    if (event.ctrlKey)
      if (event.code === "KeyN") this.newGoal();
  }

  newGoal() {
    if (!this.editing) this.editedGoal = new Goal();
  }

  /**
   * Set edited goal to null
   */
  editFinished() {
    this.editedGoal = null;
  }

  /**
   * Add a goal if a new one was created
   * @param {Goal} goal
   */
  addGoal(goal: Goal) {
    if (goal) this.module.goals.push(goal.copy());
    this.editFinished();
  }

  /**
   * Removes a goal from goals array
   * @param {Goal} goal
   */
  deleteGoal(goal: Goal) {
    let index: number;
    while (true) {
      goal.delete(); // update relations
      index = this.module.goals.indexOf(goal); // remove from array
      if (index > -1) this.module.goals.splice(index, 1);
      else break;
    }
    this.editFinished();
  }
}
