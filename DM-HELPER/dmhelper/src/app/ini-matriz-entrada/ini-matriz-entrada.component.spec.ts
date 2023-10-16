import { ComponentFixture, TestBed } from '@angular/core/testing';

import { IniMatrizEntradaComponent } from './ini-matriz-entrada.component';

describe('IniMatrizEntradaComponent', () => {
  let component: IniMatrizEntradaComponent;
  let fixture: ComponentFixture<IniMatrizEntradaComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ IniMatrizEntradaComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(IniMatrizEntradaComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
