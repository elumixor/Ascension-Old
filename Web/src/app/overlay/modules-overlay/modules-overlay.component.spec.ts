import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { ModulesOverlayComponent } from './modules-overlay.component';

describe('ModulesOverlayComponent', () => {
  let component: ModulesOverlayComponent;
  let fixture: ComponentFixture<ModulesOverlayComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ ModulesOverlayComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(ModulesOverlayComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
