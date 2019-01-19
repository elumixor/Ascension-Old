import {
  AfterViewInit, Component, ElementRef, HostListener,
  QueryList, ViewChildren, AfterViewChecked, ChangeDetectorRef
} from '@angular/core';
import {OverlayComponent} from "../overlay.component";
import {vw, vh} from "../../util/util"
import {Module, ModulesControllerService} from "../../services/modules-controller.service";

@Component({
  selector: 'app-modules-overlay',
  template: `<h5 *ngFor="let x of elements; index as i"
              [style.top.px]="x.top"
              [style.left.px]="x.left"
              [style.text-shadow]="'0 0 10px ' + x.color"
              #mark>{{x.name}}</h5>`,
  styles: [`h5 {
            position: fixed;
            margin: 0;
            color: black;
            font-size: 3rem;
          }`]
})
export class ModulesOverlayComponent implements AfterViewInit, AfterViewChecked {
  @ViewChildren("mark") viewChildren: QueryList<ElementRef>;
  private positions: {
    left: number
    top: number
    width: number
    height: number
  }[] = [];

  elements: {
    name: string,
    left: number, top: number,
    color: string,
    module: Module
  }[] = [
    {name: 'Kn', left: 0, top: 0, color: '#7a00ff', module: Module.KNOWLEDGE},
    {name: 'St', left: 0, top: 0, color: '#ff117e', module: Module.STRATGY},
  ];


  constructor(private overlay: OverlayComponent, private changeDetector: ChangeDetectorRef) {
  }

  ngAfterViewInit() {
    const angle = Math.PI * 2 / this.viewChildren.length;
    this.viewChildren.forEach((item, i) => {
      this.positions.push({
        left: Math.cos(-Math.PI / 2 - angle * i) * 20,
        top: 50 + Math.sin(-Math.PI / 2 - angle * i) * 20,
        width: item.nativeElement.clientWidth / 2,
        height: item.nativeElement.clientHeight / 2,
      });
    });
  }

  ngAfterViewChecked() {
    if (this.overlay.displayed) {
      this.viewChildren.forEach((item, i) => {
        this.elements[i].left = vw(50) + vh(this.positions[i].left) - this.positions[i].width;
        this.elements[i].top = vh(this.positions[i].top) - this.positions[i].height;
      });
    }
    this.changeDetector.detectChanges();
  }

  @HostListener('document:keyup', ['$event'])
  hideSearch(event: KeyboardEvent) {
    if (event.code === "KeyM") {
      this.overlay.close.emit();
    }
  }

  @HostListener('document:keypress', ['$event'])
  openModule(event: KeyboardEvent) {
    if (this.overlay.displayed)
      this.elements.forEach((value, index) => {
        if (event.code === 'Digit' + (index + 1)) {
          ModulesControllerService.active = value.module;
        }
      })
  }
}
