import {
  AfterViewInit, Component, ElementRef, HostListener,
  QueryList, ViewChildren, AfterViewChecked, ChangeDetectorRef
} from '@angular/core';
import {OverlayComponent} from "../overlay.component";
import {vw, vh} from "../../util/util"
import {Module, ModulesControllerService} from "../../services/modules-controller.service";

@Component({
  selector: 'app-modules-overlay',
  templateUrl: `./modules-overlay.component.html`,
  styles: [`
    .name {
        text-shadow: black 0px 0px 25px;
        color: rgba(255, 255, 255, 0.7)
    }
  `]
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
    readonly name: string,
    left: number, top: number,
    readonly color: string,
    readonly module: Module
  }[] = [
    {name: 'Home',      left: 0, top: 0, color: '#ffffffc0', module: Module.HOME},
    {name: 'Knowledge', left: 0, top: 0, color: '#7a00ffc0', module: Module.KNOWLEDGE},
    {name: 'Strategy',  left: 0, top: 0, color: '#ff117ec0', module: Module.STRATGY},
  ];

  readonly maxRows = 4;
  columns: number[] = null;

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
    this.columns = new Array(Math.floor(this.elements.length / this.maxRows) + 1);
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
        if (event.code === 'Digit' + (index)) {
          ModulesControllerService.active = value.module;
        }
      })
  }
}
