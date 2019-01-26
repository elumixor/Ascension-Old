import {
  Component,
  Input,
  ViewChild,
  ElementRef,
  Output,
  EventEmitter,
  OnInit,
  HostListener,
  AfterViewInit
} from "@angular/core";
import {Goal} from "../../../../entities/goal";
import {GoalComponent} from "../goal/goal.component";

@Component({
  selector: "app-goal-edit",
  templateUrl: "./goal-edit.component.html",
  styleUrls: ["./goal-edit.component.scss"]
})
export class GoalEditComponent implements OnInit {
  @Input() public goal: Goal;

  @ViewChild("input") input: ElementRef;

  /**
   * Edited goal
   */
  temporary: Goal;

  /**
   * Sign if anything has changed
   * @return {boolean}
   */
  get edited(): boolean { return this.temporary != null && !this.goal.equals(this.temporary); }

  @Output("cancel") _cancel = new EventEmitter<void>();
  @Output("confirm") _confirm = new EventEmitter<Goal>();
  @Output("delete") _delete = new EventEmitter<Goal>();

  /**
   * On init create a copy of an edited goal and set as temporary
   */
  ngOnInit() {
    this.input.nativeElement.focus();
    this.temporary = this.goal.copy();
  }

  /**
   * Confirm the editing of a current goal.
   * Assigns temporary goal to it's origin, or (if new goal was created) pushes it into the array
   */
  confirm() {
    if (this.goal.isEmpty) this._confirm.emit(this.temporary);
    else {
      this.goal.assign(this.temporary);
      this._confirm.emit();
    }
  }

  /**
   * Cancels edit, sets temporary goal to null, closes component
   */
  cancel() { this._cancel.emit(); }

  /**
   * Delete edited goal, emit value
   */
  delete() { this._delete.emit(this.goal); }

  /**
   * Keys event listener
   */
  @HostListener("document:keydown", ["$event"])
  showSearch(event: KeyboardEvent) {
    if (event.ctrlKey)
      if (event.code === "Enter") this.confirm();

    if (event.code === "Escape") this.cancel();
  }

  // todo
  photoChanged(event) {
    // event.target.files[0] // <- resolves to a file, can be sent as binary via http or form-data
    console.log(event.target.files[0]);

    // const reader = new FileReader();
    // reader.readAsDataURL(event.target.files[0]);
    //
    // reader.onloadend = () => {
    //
    //   (<HTMLDivElement>this.background.nativeElement).style.backgroundImage =
    //   'url(' + reader.result +');'
    // };
  }
}
