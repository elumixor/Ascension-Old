import {Component, Output, EventEmitter, Input} from "@angular/core";
import {
  trigger,
  state,
  style,
  animate,
  transition
  // ...
} from "@angular/animations";

@Component({
  selector: "app-overlay",
  template: `
            <div [@openClose]="_displayed ? 'displayed' : 'hidden'" class="fullscreen">
              <div class="fullscreen" style="background-color: rgba(0,0,0,0.8);   z-index: -10;"></div>
              <ng-content></ng-content>
            </div>`,
  styles: [],
  animations: [
    trigger("openClose", [
      state("hidden", style({
        "pointer-events": "none",
        opacity: 0
      })),
      state("displayed", style({
        "pointer-events": "auto",
        opacity: 1
      })),
      transition("hidden <=> displayed", [
        animate(".2s ease-out")
      ])
    ])
  ]
})
export class OverlayComponent {

  /**
   * Emits an event when overlay is closed
   * Is used by child components (projected via ng-content) to trigger overlay closing
   * @type {EventEmitter<void>}
   */
  @Output("close") readonly close = new EventEmitter<void>();

  private _displayed = false;

  /**
   * For animations, overlay should always be displayed, but have 0 opacity and pointer-events: none
   * We emit an event so that overlays (e.g. search overlay) could react to this (e.g. set focus on input field)
   * @type {EventEmitter<void>}
   */
  readonly inView = new EventEmitter<void>();

  /**
   * Change if the overlay should be displayed
   * @param {boolean} value
   */
  @Input("displayed")
  set displayed(value: boolean) {
    this._displayed = value;
    this.inView.emit();
  }

  /**
   * Get displayed property
   * Determines if the overlay should be displayed or not.
   * @returns {boolean}
   */
  get displayed() {
    return this._displayed;
  }
}
